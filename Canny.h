#pragma once
#include <opencv2/opencv.hpp>


class Canny
{
public:
	cv::Mat src;
	cv::Mat result;

	Canny(cv::Mat& source);

	double magnitude;
	double slope;

	void noiseReduction();
	void calculateGradient();
	void nonMaximumSuppression();
};

