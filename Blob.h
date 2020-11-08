#pragma once
#include <opencv2/opencv.hpp>

class Blob 
{
	cv::Point topLeft, bottomRight;
	std::vector<cv::Point> pixels;

public:
	void add(int x, int y);
	bool isInBlob(const int& x, const int& y);
	bool isInBlob(const cv::Point& point);
	float size();
	void draw(cv::Mat& mat);
};