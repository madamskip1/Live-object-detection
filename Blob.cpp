#include "Blob.h"

Blob::Blob()
{
	topLeft.x = INT_MAX;
	topLeft.y = INT_MAX;
	bottomRight.x = INT_MIN;
	bottomRight.y = INT_MIN;
}

void Blob::add(int x, int y)
{
	topLeft.x = std::min({ x, topLeft.x });
	topLeft.y = std::min({ y, topLeft.y });
	bottomRight.x = std::max({ x, bottomRight.x });
	bottomRight.y = std::max({ y, bottomRight.y });

	pixels.push_back(cv::Point(x, y));
};

bool Blob::isInBlob(const int& x, const int& y)
{
	for (cv::Point& point : pixels)
	{
		if (point.x == x && point.y == y)
			return true;
	}

	return false;
};

bool Blob::isInBlob(const cv::Point& point)
{
	return isInBlob(point.x, point.y);
}

float Blob::size()
{
	int dx = bottomRight.x - topLeft.x;
	int dy = bottomRight.y - topLeft.y;

	return dx * dy;
}

void Blob::draw(cv::Mat& mat)
{
	cv::rectangle(mat, topLeft, bottomRight, cv::Scalar(0, 255, 0));
}

std::pair<unsigned, unsigned> Blob::getPosition()
{
    return std::pair<unsigned, unsigned>(topLeft.x, topLeft.y);
}
