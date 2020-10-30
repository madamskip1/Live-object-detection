#include "GrayscaleConverter.h"
const float GrayscaleConverter::RED_WEIGHT = 0.299;
const float GrayscaleConverter::GREEN_WEIGHT = 0.587;
const float GrayscaleConverter::BLUE_WEIGHT = 0.114;

GrayscaleConverter::GrayscaleConverter(const cv::Mat& source) : src(source)
{
    result = cv::Mat1b::zeros(source.rows, source.cols);
}

void GrayscaleConverter::convert()
{
    int size = src.rows * src.cols;
    uchar* sourcePtr = src.data;
    uchar* resultPtr = result.data;
    float newValue;
    int blue, green, red;

    for (int i = 0; i < size; i++)
    {
        blue = *(sourcePtr++);
        green = *(sourcePtr++);
        red = *(sourcePtr++);
        newValue = calcNewValue(blue, green, red);
        *(resultPtr++) = newValue;
    }
}

cv::Mat& GrayscaleConverter::getResult()
{
    return result;
}

float GrayscaleConverter::calcNewValue(int blue, int green, int red)
{
    return blue * BLUE_WEIGHT + green * GREEN_WEIGHT + red * RED_WEIGHT;
}
