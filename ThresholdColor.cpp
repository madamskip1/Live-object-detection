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
	int imgRows = src.rows;
	int imgCols = src.cols * channels;

	uchar* sourcePtr;
	uchar* resultPtr;
	int channel = 0;

	for (int imgY = 0; imgY < imgRows; imgY++)
	{
		sourcePtr = src.ptr<uchar>(imgY);
		resultPtr = result.ptr<uchar>(imgY);

		for (int imgX = 0; imgX < imgCols; imgX++)
		{
			channel = imgX % channels;
			setThreshold(sourcePtr[imgX], resultPtr[imgX], colorsRange[channel].min, colorsRange[channel].max);
		}
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

void ThresholdColor::setThreshold(uchar& source, uchar& result, int min, int max)
{
	if (checkIfInRange((int)source, min, max))
		result = (uchar)255;
	else
		result = (uchar)0;
}

void ThresholdColorMono::filter()
{
	int channels = src.channels();
	int imgRows = src.rows;
	int imgCols = src.cols;
	
	uchar* sourcePtr;
	uchar* resultPtr;
	int srcX;
	int val;
	bool inRange;


	for (int imgY = 0; imgY < imgRows; imgY++)
	{
		sourcePtr = src.ptr<uchar>(imgY);
		resultPtr = result.ptr<uchar>(imgY);

		for (int imgX = 0; imgX < imgCols; imgX++)
		{
			srcX = imgX * channels;
			inRange = true;
			for (int i = 0; i < channels; i++)
			{
				val = (int)sourcePtr[srcX + i];

				if (!checkIfInRange(val, colorsRange[i].min, colorsRange[i].max))
					inRange = false;
			}

			if (inRange)
			{
				resultPtr[imgX] = (uchar)255;
			}
			else
			{
				resultPtr[imgX] = (uchar)0;
			}
		}
	}
}

ThresholdColorMono::ThresholdColorMono(const cv::Mat& source)
{
	src = source;
	colorsRange.resize(src.channels(), ColorRange(0, 255));
	result = cv::Mat1b::zeros(source.rows, source.cols);
}