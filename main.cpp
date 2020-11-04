#include <opencv2/opencv.hpp>
#include <iostream>
#include "FilterImage.h"
#include "ThresholdColor.h"
#include "GrayscaleConverter.h"
#include "Canny.h"
#include "BlobDetector.h"

int main()
{
	cv::VideoCapture cap;
	BlobDetector blobDetector;

	if (!cap.open(0))
		return 0;

	bool loop = true;

	while (loop)
	{
		cv::Mat frame;
		cap >> frame;
		ThresholdColorMono thres2(frame);
		thres2.setColor(3, 50, 70);
		thres2.setColor(2, 60,  80);
		thres2.setColor(1, 75, 105);
		thres2.filter();
		blobDetector.detect(thres2.getResult());
		blobDetector.draw(frame);
	
		cv::imshow("Live Pepsi Detection", frame);
		if (cv::waitKey(10) == 27)
			loop = false;
	}


	return 0;
}