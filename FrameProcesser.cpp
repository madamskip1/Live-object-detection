#include "FrameProcesser.h"
#include "globalVariables.h"

int frameProcesser()
{
    shm_unlink(PROCESSED_SHARED_MEMORY_NAME);
    shm_unlink(STAT_SHARED_MEMORY_NAME);

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
            std::cout << "SCHED_OTHER";
            break;
        case SCHED_RR:
            std::cout << "SCHED_RR";
            break;
        case SCHED_FIFO:
            std::cout << "SCHED_FIFO";
            break;
        default:
            std::cout << "Unknown...";
    }

    int fd2 = shm_open(PROCESSED_SHARED_MEMORY_NAME, O_CREAT | O_EXCL | O_RDWR,
    S_IRUSR | S_IWUSR);
    if (fd2 == -1)
        printError("shm_open");

    if (ftruncate(fd2, sizeof(img)) == -1)
    {
        throw("ftruncate");
        exit(3);
    }
    struct img *processedMemPtr = (img*) mmap(NULL, sizeof(struct img),
    PROT_READ | PROT_WRITE,
                                              MAP_SHARED, fd2, 0);

    if (processedMemPtr == MAP_FAILED)
        printError("mmap");

    if (sem_init(&processedMemPtr->sem1, 1, 0) == -1)
        printError("sem_init-sem1");
    if (sem_init(&processedMemPtr->sem2, 1, 0) == -1)
        printError("sem_init-sem2");

    int fd3 = shm_open(STAT_SHARED_MEMORY_NAME, O_CREAT | O_EXCL | O_RDWR,
    S_IRUSR | S_IWUSR);
    if (fd3 == -1)
        printError("shm_open");

    if (ftruncate(fd3, sizeof(stats)) == -1)
    {
        throw("ftruncate");
        exit(3);
    }
    struct stats *statFrameMemPtr = (stats*) mmap(NULL, sizeof(struct stats),
    PROT_READ | PROT_WRITE,
                                                  MAP_SHARED, fd3, 0);

    if (statFrameMemPtr == MAP_FAILED)
        printError("mmap");

    if (sem_init(&statFrameMemPtr->sem1, 1, 0) == -1)
        printError("sem_init-sem1");
    if (sem_init(&statFrameMemPtr->sem2, 1, 0) == -1)
        printError("sem_init-sem2");

    int fd = shm_open(FRAME_SHARED_MEMORY_NAME, O_RDWR, 0);
    if (fd == -1)
        printError("shm_open");
    struct img *readFrameMemPtr = (img*) mmap(NULL, sizeof(struct img),
    PROT_READ | PROT_WRITE,
                                              MAP_SHARED, fd, 0);

    if (readFrameMemPtr == MAP_FAILED)
        printError("mmap");

    unsigned count = 0;

    float kernel[] = { 1, 1, 1,
                       1,
                       1, 1,
                       1,
                       1, 1 };

    std::ofstream file("frameProcesser.txt");
    if (!file.is_open())
        printError("file not open");

    file << "processingTime ; waitTime" << std::endl;

    auto startWait = std::chrono::steady_clock::now();
    auto endWait = std::chrono::steady_clock::now();

    while (count < FRAME_COUNT)
    {

        if (sem_wait(&readFrameMemPtr->sem1) == -1)
            printError("sem_wait");

        auto start = std::chrono::steady_clock::now();

        cv::Mat image(ROWS, COLS, CV_8UC3, readFrameMemPtr->imgData);
        BGRToHSVConverter converter(image);
        converter.convert();
        ThresholdColorMono mono(converter.getResult());
        mono.setColor(1, 165, 180);
        mono.setColor(2, 170, 255);
        mono.setColor(3, 130, 205);
        mono.filter();
        FilterImage dilate(mono.getResult());
        dilate.setKernel(kernel, 3);
        dilate.filter();
        BlobDetector detector;
        detector.detect(dilate.getResult());
        detector.draw(image);
        cv::Mat cl = image.clone();
        memcpy(processedMemPtr->imgData, cl.ptr(0), COLS * ROWS * 3);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> time = end - start;

        const auto detectionTuple = detector.getDetection();
        statFrameMemPtr->detected = std::get<0>(detectionTuple);
        statFrameMemPtr->x = std::get<1>(detectionTuple);
        statFrameMemPtr->y = std::get<2>(detectionTuple);
        statFrameMemPtr->processingTime = time.count();

        std::chrono::duration<double, std::milli> waitTime = endWait
                                                             - startWait;
        file << std::setprecision(12) << time.count() << ";" << waitTime.count()
             << std::endl;

        if (sem_post(&readFrameMemPtr->sem2) == -1)
            printError("sem_post");

        if (sem_post(&processedMemPtr->sem1) == -1)
            printError("sem_post");

        if (sem_post(&statFrameMemPtr->sem1) == -1)
            printError("sem_post");

        startWait = std::chrono::steady_clock::now();

        if (sem_wait(&processedMemPtr->sem2) == -1)
            printError("sem_wait");

        if (sem_wait(&statFrameMemPtr->sem2) == -1)
            printError("sem_wait");

        endWait = std::chrono::steady_clock::now();

        count++;
    }

    file.close();
    shm_unlink(PROCESSED_SHARED_MEMORY_NAME);
    shm_unlink(STAT_SHARED_MEMORY_NAME);

    return 0;
}

