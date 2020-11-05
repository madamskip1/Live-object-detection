#pragma once
#include <opencv2/opencv.hpp>

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
	int saturation(int max, int delta);
};

