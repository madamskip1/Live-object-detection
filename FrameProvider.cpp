#include "FrameProvider.h"

#include <opencv2/opencv.hpp>
#include "globalVariables.h"
#include "BlobDetector.h"
#include <iostream>

int frameProvider(int argc, char *argv[])
{
    shm_unlink(FRAME_SHARED_MEMORY_NAME);

    const int core_id = 0;
    const pid_t pid = getpid();
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    const int set_result = sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset);
    if (set_result != 0)
        printError("sched_setaffinity ERROR");

    const int get_affinity = sched_getaffinity(pid, sizeof(cpu_set_t), &cpuset);
    if (get_affinity != 0)
        printError("sched_getaffinity ERROR");

    if (!CPU_ISSET(core_id, &cpuset))
        printError("Failed to set process affinity");

    sched_param sp = { .sched_priority = sched_get_priority_max(SCHED) };
    int ret;

    ret = sched_setscheduler(pid, SCHED, &sp);
    if (ret == -1)
        perror("sched_setscheduler");

    int policy = sched_getscheduler(pid);

    switch (policy)
    {
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        default:
            printf("Unknown...\n");
    }

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s sending-frequency[Hz]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ptr = argv[1];
    int dotts = 0;

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(*(ptr + i)) == 0 && *(ptr + i) != '.')
        {
            fprintf(stderr,
                    "Sending-frequency[Hz] needs to be a double value\n");
            exit(EXIT_FAILURE);
        } else if (*(ptr + i) == '.')
        {
            dotts++;
            if (dotts > 1)
            {
                fprintf(stderr,
                        "Sending-frequency[Hz] needs to be a double value\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    double freq = atof(argv[1]);

    if (freq == 0.0)
    {
        throw("Sending-frequency[Hz] cannot be equal to 0\n");
        exit(3);
    }

    int fd = shm_open(FRAME_SHARED_MEMORY_NAME, O_CREAT | O_EXCL | O_RDWR,
    S_IRUSR | S_IWUSR);
    if (fd == -1)
        printError("shm_open");

    if (ftruncate(fd, sizeof(img)) == -1)
        printError("ftruncate");

    img *imgPtr = (img*) mmap(NULL, sizeof(struct img),
    PROT_READ | PROT_WRITE,
                              MAP_SHARED, fd, 0);
    if (imgPtr == MAP_FAILED)
        printError("mmap");

    if (sem_init(&imgPtr->sem1, 1, 0) == -1)
        printError("sem_init-sem1");

    if (sem_init(&imgPtr->sem2, 1, 0) == -1)
        printError("sem_init-sem2");

    cv::VideoCapture cap;

    if (!cap.open(0))
        return 0;

    struct timespec start, stop;
    double time;
    int count = 0;

    while (count < FRAME_COUNT)
    {

        cv::Mat frame;
        cap >> frame;
        cv::Mat cl = frame.clone();
        memcpy(imgPtr->imgData, cl.ptr(0), COLS * ROWS * 3);

        if (clock_gettime(CLOCK_REALTIME, &start) == -1)
            printError("clock gettime");

        time = start.tv_sec + (double) (start.tv_nsec) / 1000000;
//        std::cout << time << ";;";

        if (sem_post(&imgPtr->sem1) == -1)
            printError("sem_post");

        delay(1 / freq);

        if (sem_wait(&imgPtr->sem2) == -1)
            printError("sem_wait");

        count++;
    }

    shm_unlink(FRAME_SHARED_MEMORY_NAME);
    return 0;
}
