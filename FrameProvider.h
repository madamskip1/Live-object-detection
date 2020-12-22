#ifndef FRAMEPROVIDER_H_
#define FRAMEPROVIDER_H_

#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <chrono>

#include "globalVariables.h"
#include "globalFunctions.hpp"

int frameProvider(int argc, char *argv[]);

#endif /* FRAMEPROVIDER_H_ */
