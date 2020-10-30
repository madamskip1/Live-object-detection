#pragma once
#include <opencv2/opencv.hpp>

class FilterImage
{
private:
	cv::Mat src;
	cv::Mat result;
	cv::Mat kernel;

public:
	FilterImage(const cv::Mat& source);
	FilterImage(const cv::Mat& source, const cv::Mat& kernel);
	void setKernel(const cv::Mat& newKernel);
	void filter();
	cv::Mat& getResult();

private:
	template<typename T>
	void trimValue(T& value, const T& min, const T& max);
	void setNewValues(uchar* row, int col, float val1, float val2, float val3);
	bool checkIfPointIsInside(int x, int y, int width, int height);
};

