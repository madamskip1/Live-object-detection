#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

class MergeMat
{
public:
	MergeMat() {};
	cv::Mat result;

	void bitAnd(cv::Mat& src1, cv::Mat& src2)
	{
		result = cv::Mat1b::zeros(src1.rows, src1.cols);
		int cols = src1.cols;
		int rows = src2.rows;
		uchar* src1Ptr;
		uchar* src2Ptr;
		uchar* resultPtr;

		for (int y = 0; y < rows; y++)
		{
			src1Ptr = src1.ptr<uchar>(y);
			src2Ptr = src2.ptr<uchar>(y);
			resultPtr = result.ptr<uchar>(y);
			
			for (int x = 0; x < cols; x++)
			{
				if (src1Ptr[x] == 255 && src2Ptr[x] == 255)
					resultPtr[x] = (uchar)255;
				else
					resultPtr[x] = (uchar)0;
			}

		}
	}

	void bitOr(cv::Mat& src1, cv::Mat& src2)
	{
		result = cv::Mat1b::zeros(src1.rows, src1.cols);
		int cols = src1.cols;
		int rows = src2.rows;
		uchar* src1Ptr;
		uchar* src2Ptr;
		uchar* resultPtr;

		for (int y = 0; y < rows; y++)
		{
			src1Ptr = src1.ptr<uchar>(y);
			src2Ptr = src2.ptr<uchar>(y);
			resultPtr = result.ptr<uchar>(y);

			for (int x = 0; x < cols; x++)
			{
				if (src1Ptr[x] == 255 || src2Ptr[x] == 255)
					resultPtr[x] = (uchar)255;
				else
					resultPtr[x] = (uchar)0;
			}

		}
	}

	void bitAnd(std::vector<cv::Mat> sources)
	{
		result = cv::Mat1b::zeros(sources[0].rows, sources[0].cols);
		int cols = sources[0].cols;
		int rows = sources[0].rows;
		int size = sources.size();
		std::vector<uchar*> sourcesPtr;
		sourcesPtr.resize(size);
		uchar* resultPtr;
		bool set;

		for (int y = 0; y < rows; y++)
		{
			for (int i = 0; i < size; i++)
				sourcesPtr[i] = sources[i].ptr<uchar>(y);

			resultPtr = result.ptr<uchar>(y);

			for (int x = 0; x < cols; x++)
			{
				set = true;
				for (int i = 0; i < size; i++)
				{
					if (sourcesPtr[i][x] == 0)
					{
						set = false;
						i = size;
						resultPtr[x] = (uchar)0;
					}
				}

				if (set)
					resultPtr[x] = (uchar)255;
			}

		}
	}

	void bitOr(std::vector<cv::Mat> sources)
	{
		result = cv::Mat1b::zeros(sources[0].rows, sources[0].cols);
		int cols = sources[0].cols;
		int rows = sources[0].rows;
		int size = sources.size();
		std::vector<uchar*> sourcesPtr;
		sourcesPtr.resize(size);
		uchar* resultPtr;
		bool set;

		for (int y = 0; y < rows; y++)
		{
			for (int i = 0; i < size; i++)
				sourcesPtr[i] = sources[i].ptr<uchar>(y);

			resultPtr = result.ptr<uchar>(y);

			for (int x = 0; x < cols; x++)
			{
				set = false;
				for (int i = 0; i < size; i++)
				{
					if (sourcesPtr[i][x] == 255)
					{
						set = set;
						i = size;
						resultPtr[x] = (uchar)255;
					}
				}

				if (!set)
					resultPtr[x] = (uchar)0;
			}

		}
	}
};

