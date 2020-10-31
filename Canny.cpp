#include "Canny.h"
#include "FilterImage.h"
#include "GradientCalculator.h"


Canny::Canny(cv::Mat& source) : src(source)
{
}


void Canny::noiseReduction()
{
	FilterImage filter(src);
	float gaussianBlur[] = {
		1.0f, 4.0f,  6.0f,  4.0f,  1.0f,
		4.0f, 16.0f, 24.0f, 16.0f, 4.0f,
		6.0f, 24.0f, 36.0f, 24.0f, 6.0f,
		4.0f, 16.0f, 24.0f, 16.0f, 4.0f,
		1.0f, 4.0f,  6.0f,  4.0f,  1.0f
	};
	int gaussianSum = 256;
	for (int i = 0; i < 5 * 5; i++)
		gaussianBlur[i] /= gaussianSum;

	filter.setKernel(gaussianBlur, 5);
	filter.filter();
	cv::imshow("noise", filter.getResult());

	filter.getResult().copyTo(result);
}

void Canny::calculateGradient()
{
	float sobelX[] = {
		-1.0f / 9, 0.0f, 1.0f / 9,
		-2.0f / 9, 0.0f, 2.0f / 9,
		-1.0f / 9, 0.0f, 1.0f / 9
	};
	float sobelY[] = {
		1.0f / 9, 2.0f / 9, 1.0f / 9,
		0.0f, 0.0f, 0.0f,
		-1.0f / 9, -2.0f, -1.0f / 9
	};

	FilterImage deriY(result);
	deriY.setKernel(sobelY, 3);
	deriY.filter();
	cv::imshow("sobelY", deriY.getResult());

	FilterImage deriX(result);
	deriX.setKernel(sobelX, 3);
	deriX.filter();
	cv::imshow("sobelX", deriX.getResult());

	GradientCalculator gradient(deriX.getResult(), deriY.getResult());
	gradient.calculate();

	cv::imshow("gradient", gradient.getResult());
}

