#pragma once
#include <opencv2/opencv.hpp>
#include "Blob.h"

class BlobDetector
{
public:
	std::vector<Blob> blobs;
	int distanceThreshold;

	void detect(cv::Mat& src)
	{
		blobs.clear();
		int rows = src.rows;
		int cols = src.cols;
		uchar* row;
		bool found;
		for (int y = 0; y < rows; y++)
		{
			row = src.ptr<uchar>(y);

			for (int x = 0; x < cols; x++)
			{
				if (row[x] ==  (uchar)255)
				{
					found = false;

					for (Blob& b : blobs)
					{
						if (b.isNear(x, y, 10))
						{
							b.add(x, y);
							found = true;
							break;
						}
					}

					if (!found)
					{
						blobs.push_back(Blob(x, y));
					}

				}
			}
		}
	}

	void draw(cv::Mat& mat)
	{
		for (Blob& b : blobs)
		{
			if (b.size() > 500)
			{
				cv::rectangle(mat, b.topLeft, b.bottomRight, cv::Scalar(0, 255, 0));
			}
		}
	}
};

