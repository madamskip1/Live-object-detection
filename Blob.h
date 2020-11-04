#pragma once
#include <opencv2/opencv.hpp>

class Blob
{
public:
	cv::Point topLeft, bottomRight;
	cv::Point center;
	Blob(int x, int y)
	{
		topLeft.x = bottomRight.x = center.x = x;
		topLeft.y = bottomRight.y = center.y = y;
	}

	bool isNear(int x, int y, int threshold)
	{
		//float distance = calcDistance(x, y);
		//if (distance <= threshold)
		//	return true;

		//return false;

		float dX = std::max({ topLeft.x - x, 0, x - bottomRight.x });
		float dY = std::max({ topLeft.y - y, 0, y - bottomRight.y });
		float distance = sqrt(dX * dX + dY * dY);
		
		if (distance <= threshold)
			return true;

		return false;
	}

	void add(int x, int y)
	{
		topLeft.x = std::min({ x, topLeft.x });
		topLeft.y = std::min({ y, topLeft.y });
		bottomRight.x = std::max({ x, bottomRight.x });
		bottomRight.y = std::max({ y, bottomRight.y });

		calcCenter();
	}

	float calcDistance(int x, int y)
	{
		int dX = center.x - x;
		int dY = center.y - y;

		return sqrt(dX * dX + dY * dY);
	}

	void calcCenter()
	{
		center.x = (topLeft.x + bottomRight.x) / 2;
		center.y = (topLeft.y + bottomRight.y) / 2;
	}

	float size()
	{
		int dx = bottomRight.x - topLeft.x;
		int dy = bottomRight.y - topLeft.y;

		return dx * dy;
	}
};