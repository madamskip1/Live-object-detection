#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "Blob.h"
#include <tuple>

class BlobDetector
{
private:
	std::vector<std::shared_ptr<Blob>> blobs;
	std::tuple<bool, unsigned, unsigned> detection{false,0,0};
public:
	void detect(const cv::Mat& src);
	bool draw(cv::Mat& mat);
	int numberOfBlobs();
	std::vector<std::shared_ptr<Blob>>& getBlobs();
	std::shared_ptr<Blob> getBlob(int index);
	std::tuple<bool, unsigned, unsigned> getDetection();
};

