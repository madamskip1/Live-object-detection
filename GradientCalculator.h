#pragma once
#include <opencv2/opencv.hpp>

class GradientCalculator
{
public:
	cv::Mat src1;
	cv::Mat src2;
	cv::Mat result;

	GradientCalculator(const cv::Mat& src1, const cv::Mat& src2);
	void calculate();
	float newValue(int x, int y);
	cv::Mat& getResult();
};

