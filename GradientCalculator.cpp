#include "GradientCalculator.h"

GradientCalculator::GradientCalculator(const cv::Mat& src1, const cv::Mat& src2) : src1(src1), src2(src2)
{
	result = cv::Mat1b::zeros(src1.rows, src1.cols);
}

void GradientCalculator::calculate()
{
	int size = src1.rows * src2.cols;
	uchar* src1Ptr = src1.data;
	uchar* src2Ptr = src2.data;
	uchar* resultPtr = result.data;

	int x, y;

	for (int i = 0; i < size; i++)
	{
		x = *(src1Ptr++);
		y = *(src2Ptr++);

		*(resultPtr++) = (uchar)newValue(x, y);
	}
}

float GradientCalculator::newValue(int x, int y)
{
	return sqrt(x * x + y * y);
}

cv::Mat& GradientCalculator::getResult()
{
	return result;
}


