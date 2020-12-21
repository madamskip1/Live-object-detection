#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

struct ColorRange
{
	int min;
	int max;
	ColorRange(int min_, int max_)
	{
		min = min_;
		max = max_;
	};
};


class ThresholdColor
{
protected:
	cv::Mat src;
	cv::Mat result;
	std::vector<ColorRange> colorsRange;

public:
	ThresholdColor(const cv::Mat& source);
	void setColor(int channel, int min, int max);
	void setColor(int channel, const ColorRange& range);
	virtual void filter();
	cv::Mat& getResult();
protected:
	ThresholdColor() {};
	bool checkIfInRange(const int& values, int min, int max);
	void setThreshold(uchar& source, uchar& result, int min, int max);
};

class ThresholdColorMono
	: public ThresholdColor
{
public:
	ThresholdColorMono(const cv::Mat& source);
	void filter();
};