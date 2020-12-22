#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_

#include <semaphore.h>
#define BILLION 1000000000L
#define SCHED SCHED_FIFO

static constexpr const char *FRAME_SHARED_MEMORY_NAME = "frameshmem";
static constexpr const char *PROCESSED_SHARED_MEMORY_NAME = "processedshmem";
static constexpr const char *STAT_SHARED_MEMORY_NAME = "statshmem";

static constexpr unsigned ROWS { 720 };
static constexpr unsigned COLS { 1280 };
static constexpr unsigned FRAME_COUNT { 250 };


struct img
{
    sem_t sem1;
    sem_t sem2;
    float imgData[ROWS * COLS*3];
};

struct stats
{
    sem_t sem1;
    sem_t sem2;
    double processingTime;
    bool detected;
    unsigned x;
    unsigned y;
};

#endif /* GLOBALVARIABLES_H_ */
