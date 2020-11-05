#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
class BGRToHSVConverter
{
public:
	BGRToHSVConverter(const cv::Mat& source);

	void convert();
	cv::Mat& getResult();

private:
	cv::Mat src;
	cv::Mat result;

	int hue(int b, int g, int r, int max, int delta);
	int saturation(const int& max, const int& delta);
};

