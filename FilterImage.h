#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

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
	void setKernel(float newKernel[], int size);
	void filter();
	cv::Mat& getResult();

private:
	template<typename T>
	void trimValue(T& value, const T& min, const T& max);
	void setNewValues(uchar* row, const int col, std::vector<float>& values);
	bool checkIfPointIsInside(const int& x, const int& y, const int& width, const int& height);
	bool checkIfBetween(const int& val, const int& min, const int& max);
};

