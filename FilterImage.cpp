#include "FilterImage.h"
#include <iostream>

FilterImage::FilterImage(const cv::Mat & source) : src(source)
{
	result = cv::Mat_<cv::Vec3b>::zeros(cv::Size(source.rows, source.cols));
}

FilterImage::FilterImage(const cv::Mat& source, const cv::Mat& kernel) : src(source), kernel(kernel)
{
	result = cv::Mat_<cv::Vec3b>::zeros(cv::Size(source.rows, source.cols));
}

void FilterImage::filter()
{
	int kernelRows = kernel.rows;
	int kernelCols = kernel.cols;
	int fromCenterX = kernelCols / 2;
	int fromCenterY = kernelRows / 2;
	float kernelValue;
	
	int channels = src.channels();
	int imgRows = src.rows;
	int imgCols = src.cols * channels;

	float newValue1;
	float newValue2;
	float newValue3;
	
	uchar* resultRow;
	uchar* pixelsToMaskRow;
	float* kernelRow;

	int valueSourceX;
	int valueSourceY;

	for (int imgY = 0; imgY < imgRows; imgY++)
	{
		resultRow = result.ptr<uchar>(imgY);
		for (int imgX = 0; imgX < imgCols; imgX = imgX + 3)
		{
			newValue1 = 0;
			newValue2 = 0;
			newValue3 = 0;

			kernelRow = reinterpret_cast<float*>(kernel.data);

			for (int kernelY = 0; kernelY < kernelRows; kernelY++)
			{
				valueSourceY = imgY - fromCenterY + kernelY;

				if (valueSourceY >= 0 && valueSourceY < imgRows)
				{
					pixelsToMaskRow = src.ptr<uchar>(valueSourceY);

					for (int kernelX = 0; kernelX < kernelCols; kernelX++)
					{
						valueSourceX = imgX - (fromCenterX + kernelX) * channels;
						
						if (valueSourceX >= 0 && valueSourceX < imgCols)
						{
							kernelValue = *kernelRow;

							newValue1 += kernelValue * (int)pixelsToMaskRow[valueSourceX];
							newValue2 += kernelValue * (int)pixelsToMaskRow[valueSourceX + 1];
							newValue3 += kernelValue * (int)pixelsToMaskRow[valueSourceX + 2];
						}

						++kernelRow;
					}
				}
				else
					kernelRow += kernelCols;
			}

			setNewValues(resultRow, imgX, newValue1, newValue2, newValue3);
		}

	}
}

cv::Mat& FilterImage::getResult()
{
	return result;
}

bool FilterImage::checkIfPointIsInside(int x, int y, int width, int height)
{
	return (x >= 0 && x < width&& y >= 0 && y < height);
}

void FilterImage::setKernel(const cv::Mat& newKernel)
{
	kernel = newKernel;
}


void FilterImage::setNewValues(uchar* row, int col, float val1, float val2, float val3)
{
	trimValue(val1, 0.0f, 255.0f);
	trimValue(val2, 0.0f, 255.0f);
	trimValue(val3, 0.0f, 255.0f);
	row[col] = (uchar)val1;
	row[col + 1] = (uchar)val2;
	row[col + 2] = (uchar)val3;

}

template<typename T>
void FilterImage::trimValue(T& value, const T& min, const T& max)
{
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
}
	