#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "Blob.h"

class BlobDetector
{
	std::vector<std::shared_ptr<Blob>> blobs;

public:
	void detect(const cv::Mat& src);
	void blobSearch(std::shared_ptr<Blob> blob, cv::Mat& mat, int x, int y);
	void draw(cv::Mat& mat);
	int numberOfBlobs();
	std::vector<std::shared_ptr<Blob>>& getBlobs();
	std::shared_ptr<Blob> getBlob(int index);
};

