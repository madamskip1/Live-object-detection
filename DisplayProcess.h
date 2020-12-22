#ifndef DISPLAYPROCESS_H_
#define DISPLAYPROCESS_H_

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

int frameDisplayer();
void delay(double seconds);

#endif /* DISPLAYPROCESS_H_ */
