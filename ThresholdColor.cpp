#include "ThresholdColor.h"
#include <vector>

ThresholdColor::ThresholdColor()
{
}

ThresholdColor::ThresholdColor(const cv::Mat& source) : src(source)
{
	colorsRange = { ColorRange(0, 255), ColorRange(0, 255), ColorRange(0, 255) };
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
	int size = src.rows * src.cols;

	uchar* sourcePtr = src.data;
	uchar* resultPtr = result.data;

	for (int i = 0; i < size; i++)
	{
		setThreshold(sourcePtr++, resultPtr++, colorsRange[0].min, colorsRange[0].max);
		setThreshold(sourcePtr++, resultPtr++, colorsRange[1].min, colorsRange[1].max);
		setThreshold(sourcePtr++, resultPtr++, colorsRange[2].min, colorsRange[2].max);
	}
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
	int size = src.rows * src.cols;

	uchar* sourcePtr = src.data;
	uchar* resultPtr = result.data;
	int val1;
	int val2;
	int val3;

	for (int i = 0; i < size; i++)
	{
		val1 = *(sourcePtr++);
		val2 = *(sourcePtr++);
		val3 = *(sourcePtr++);

		if (checkIfInRange(val1, colorsRange[0].min, colorsRange[0].max)
			&& checkIfInRange(val2, colorsRange[1].min, colorsRange[1].max)
			&& checkIfInRange(val3, colorsRange[2].min, colorsRange[2].max))
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
	colorsRange = { ColorRange(0, 255), ColorRange(0, 255), ColorRange(0, 255) };
	result = cv::Mat1b::zeros(source.rows, source.cols);
}