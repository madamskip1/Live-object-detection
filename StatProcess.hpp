#ifndef STATPROCESS_HPP_
#define STATPROCESS_HPP_

#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>

#include "globalVariables.h"
#include "globalFunctions.hpp"

int statProcess();

#endif /* STATPROCESS_HPP_ */
