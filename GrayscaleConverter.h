#pragma once
#include <opencv2/opencv.hpp>

class GrayscaleConverter
{
public:
	static const float RED_WEIGHT;
	static const float GREEN_WEIGHT;
	static const float BLUE_WEIGHT;

private:
	cv::Mat src;
	cv::Mat result;

public:
	GrayscaleConverter(const cv::Mat& source);
	void convert();
	cv::Mat& getResult();
private:
	float calcNewValue(int blue, int green, int red);
};

