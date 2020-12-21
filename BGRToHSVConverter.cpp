#include "BGRToHSVConverter.h"
#include <iostream>
BGRToHSVConverter::BGRToHSVConverter(const cv::Mat& source) : src(source)
{
	result = cv::Mat(src.rows, src.cols, src.type());
}

void BGRToHSVConverter::convert()
{
	int imgRows = src.rows;
	int imgCols = src.cols * 3;

	int b, g, r;
	int h, s, v;
	int max, min;
	int delta;

	uchar* resultRow;
	uchar* sourceRow;

	for (int imgY = 0; imgY < imgRows; imgY++)
	{
		sourceRow = src.ptr<uchar>(imgY);
		resultRow = result.ptr<uchar>(imgY);
		for (int imgX = 0; imgX < imgCols; imgX = imgX + 3)
		{

			// Przechowuje HSV w formacie jak OpenCV:
			// H [0, 179]
			// S [0, 255]
			// V [0, 255]
			// Odpowiednio w kolejnych kolumnach

			b = (int)sourceRow[imgX];
			g = (int)sourceRow[imgX + 1];
			r = (int)sourceRow[imgX + 2];
			
			min = std::min({ b, g, r });
			max = std::max({ b, g, r });
			delta = max - min;


			if (max == min)
				h = 0;
			else
				h = hue(b, g, r, max, delta);

			s = saturation(max, delta);
			v = max;

			resultRow[imgX] = (uchar)h;
			resultRow[imgX + 1] = (uchar)s;
			resultRow[imgX + 2] = (uchar)v;
		}
	}
}
cv::Mat& BGRToHSVConverter::getResult()
{
	return result;
}
int BGRToHSVConverter::hue(int b, int g, int r, int max, int delta)
{
	float h;

	if (max == r)
	{
		h = (float)(g - b) / delta;
	}
	else if (max == g)
	{
		h = (float)(b - r) / delta;
		h += 2;
	}
	else if (max == b)
	{
		h = (float)(r - g) / delta;
		h += 4;
	}

	h *= 30;

	if (h < 0)
		h += 180;

	return (int)h;
}

int BGRToHSVConverter::saturation(const int& max, const int& delta)
{
	if (max == 0)
		return 0;

	float result = (float)delta / max * 255;

	return (int)result;
}
