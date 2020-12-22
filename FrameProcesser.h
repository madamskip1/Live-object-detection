#ifndef FRAMEPROCESSER_H_
#define FRAMEPROCESSER_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <chrono>

#include "FilterImage.h"
#include "ThresholdColor.h"
#include "GrayscaleConverter.h"
#include "Canny.h"
#include "BlobDetector.h"
#include "BGRToHSVConverter.h"
#include "MergeMat.h"
#include "globalFunctions.hpp"

int frameProcesser();

#endif
