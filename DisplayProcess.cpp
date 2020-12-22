#include "DisplayProcess.h"

int frameDisplayer()
{
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

    struct sched_param sp = { .sched_priority = sched_get_priority_max(SCHED) };
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

    int fd = shm_open(PROCESSED_SHARED_MEMORY_NAME, O_RDWR, 0);
    if (fd == -1)
        printError("shm_open");

    struct img *shmp = (img*) mmap(NULL, sizeof(struct img),
    PROT_READ | PROT_WRITE,
                                   MAP_SHARED, fd, 0);

    if (shmp == MAP_FAILED)
        printError("mmap");

    unsigned count = 0;

    std::ofstream file("displayProcess.txt");
    if (!file.is_open())
        printError("file not open");

    file << "processingTime ; waitTime" << std::endl;

    auto startWait = std::chrono::steady_clock::now();
    auto endWait = std::chrono::steady_clock::now();

    while (count < FRAME_COUNT)
    {
        startWait = std::chrono::steady_clock::now();

        if (sem_wait(&shmp->sem1) == -1)
            printError("sem_wait");
        endWait = std::chrono::steady_clock::now();
        auto start = std::chrono::steady_clock::now();

        cv::Mat image(ROWS, COLS, CV_8UC3, shmp->imgData);
        cv::imshow("Object Detection", image);
        cv::waitKey(10);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> time = end - start;
        std::chrono::duration<double, std::milli> waitTime = endWait - startWait;
        file << std::setprecision(12) << time.count() << ";" << waitTime.count() << std::endl;

        if (sem_post(&shmp->sem2) == -1)
            printError("sem_post");

        count++;
    }

    file.close();
    exit(EXIT_SUCCESS);
    return 0;
}
