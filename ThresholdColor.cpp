#include "ThresholdColor.h"
#include <vector>
ThresholdColor::ThresholdColor(const cv::Mat& source) : src(source)
{
	colorsRange.resize(src.channels(), ColorRange(0, 255));
	result = cv::Mat3b::zeros(source.rows, source.cols);
}

void ThresholdColor::setColor(int channel, int min, int max)
{
	colorsRange[channel - 1] =  ColorRange(min, max);
}

void ThresholdColor::setColor(int channel, const ColorRange& range)
{
	colorsRange[channel] = range;
}

void ThresholdColor::filter()
{
	int channels = src.channels();
	int size = src.rows * src.cols * channels;

	int channel = 0;
	uchar* sourcePtr = src.data;
	uchar* resultPtr = result.data;

	for (int i = 0; i < size; i++)
	{
		channel = i % channels;
		setThreshold(sourcePtr++, resultPtr++, colorsRange[channel].min, colorsRange[channel].max);
	}
}

cv::Mat& ThresholdColor::getResult()
{
	return result;
}




bool ThresholdColor::checkIfInRange(const int& values, int min, int max)
{
	return (values >= min && values <= max);
}

void ThresholdColor::setThreshold(uchar* sourcePtr, uchar* resultPtr, int min, int max)
{
	if (checkIfInRange(*sourcePtr, min, max))
		*resultPtr = (uchar)255;
	else
		*resultPtr = (uchar)0;
}

void ThresholdColorMono::filter()
{
	int channels = src.channels();
	int size = src.rows * src.cols ;
	bool inRange;

	uchar* sourcePtr = src.data;
	uchar* resultPtr = result.data;
	int val;

	for (int i = 0; i < size; i++)
	{
		inRange = true;
		for (int i = 0; i < channels; i++)
		{
			val = *(sourcePtr++);
			if (!checkIfInRange(val, colorsRange[i].min, colorsRange[i].max))
			{
				inRange = false;
			}
		}


		if (inRange)
		{
			*(resultPtr++) = (uchar)255;
		}
		else
		{
			*(resultPtr++) = (uchar)0;
		}


	}
}

ThresholdColorMono::ThresholdColorMono(const cv::Mat& source)
{
	src = source;
	colorsRange.resize(src.channels(), ColorRange(0, 255));
	result = cv::Mat1b::zeros(source.rows, source.cols);
}