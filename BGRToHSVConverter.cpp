#include "BGRToHSVConverter.h"

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
		for (int imgX = 0; imgX < imgCols; imgX = imgX + 3)
		{
			sourceRow = src.ptr<uchar>(imgY);
			resultRow = src.ptr<uchar>(imgY);

			// Przechowuje HSV w formacie jak OpenCV:
			// H [0, 179]
			// S [0, 255]
			// V [0, 255]
			// Odpowiednio w kolejnych kolumnach

			b = sourceRow[imgX];
			g = sourceRow[imgX + 1];
			r = sourceRow[imgX + 2];

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
	int h;

	if (max == r)
		h = ((60 * ((g - b) / delta) + 360) % 360);
	else if (max == g)
		h = ((60 * ((b - r) / delta) + 360) % 360);
	else if (max == b)
		h = ((60 * ((r - g) / delta) + 360) % 360);

	h /= 2; // w tej chwili [0, 359]. Dzielenie przez dwa => [0, 179] jak w openCV

	return h;
}

int BGRToHSVConverter::saturation(int max, int delta)
{
	if (max == 0)
		return 0;

	return delta / max * 255;
}
