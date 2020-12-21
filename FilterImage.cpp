#include "FilterImage.h"
#include <iostream>
#include <vector>

FilterImage::FilterImage(const cv::Mat& source) : src(source)
{
	result = cv::Mat(src.rows, src.cols, src.type());
}

FilterImage::FilterImage(const cv::Mat& source, const cv::Mat& kernel) : src(source), kernel(kernel)
{
	result = cv::Mat(src.rows, src.cols, src.type());
}

void FilterImage::filter()
{
	
	int channels = src.channels();
	int imgRows = src.rows;
	int imgCols = src.cols;

	int kernelSize = kernel.rows;
	int fromCenter = kernelSize / 2;
	float kernelValue;
	 
	std::vector<float> newValues;
	newValues.resize(channels, 0);

	uchar* resultRow;
	uchar* sourceRow;
	float* kernelRow;

	int sourceX;
	int sourceY;

	for (int imgY = 0; imgY < imgRows; imgY++)
	{
		resultRow = result.ptr<uchar>(imgY);
		for (int imgX = 0; imgX < imgCols; imgX++)
		{
			std::fill(newValues.begin(), newValues.end(), 0);
			for (int kernelY = 0; kernelY < kernelSize; kernelY++)
			{
				kernelRow = kernel.ptr<float>(kernelY);

				sourceY = imgY - fromCenter + kernelY;
				if (checkIfBetween(sourceY, 0, imgRows - 1))
				{
					sourceRow = src.ptr<uchar>(sourceY);

					for (int kernelX = 0; kernelX < kernelSize; kernelX++)
					{
						sourceX = (imgX - fromCenter + kernelX);
						if (checkIfBetween(sourceX, 0, (imgCols - 1)))
						{
							kernelValue = kernelRow[kernelX];
							sourceX *= channels;
							for (int channel = 0; channel < channels; channel++)
							{
								newValues[channel] += kernelValue * (float)sourceRow[sourceX + channel];
							}
						}
					}
				}

			}
			setNewValues(resultRow, imgX * channels, newValues);
		}
	}

}

cv::Mat& FilterImage::getResult()
{
	return result;
}

bool FilterImage::checkIfPointIsInside(const int& x, const int& y, const int& width, const int& height)
{
	return (x >= 0 && x < width&& y >= 0 && y < height);
}

bool FilterImage::checkIfBetween(const int& val, const int& min, const int& max)
{
	return (val >= min && val <= max);
}

void FilterImage::setKernel(const cv::Mat& newKernel)
{
	kernel = newKernel;
}

void FilterImage::setKernel(float newKernel[], int size)
{
	kernel = cv::Mat(size, size, CV_32F, newKernel);
}


void FilterImage::setNewValues(uchar* row, const int col, std::vector<float>& values)
{
	for (int i = 0; i < values.size(); i++)
	{
		values[i] = abs(values[i]);
		trimValue(values[i], 0.0f, 255.0f);
		row[col + i] = (uchar)values[i];
	}

}

template<typename T>
void FilterImage::trimValue(T& value, const T& min, const T& max)
{
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
}
	