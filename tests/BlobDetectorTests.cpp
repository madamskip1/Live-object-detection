#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch2/catch.hpp"
#include <vector>
#include "../BlobDetector.h"
#include "../Blob.h"

TEST_CASE("one blob", "[oneBlob]")
{
	uchar data[] = { 0, 255, 0,
					255, 255, 255,
					0, 0, 0,
	};

	cv::Mat test = cv::Mat(3, 3, CV_8UC1, data);

	BlobDetector detector;
	detector.detect(test);

	REQUIRE(detector.numberOfBlobs() == 1);
	std::shared_ptr<Blob> blob = detector.getBlob(0);
	REQUIRE(!blob->isInBlob(0, 0));
	REQUIRE(blob->isInBlob(1, 0));
	REQUIRE(!blob->isInBlob(2, 0));
	REQUIRE(blob->isInBlob(0, 1));
	REQUIRE(blob->isInBlob(1, 1));
	REQUIRE(blob->isInBlob(2, 1));
	REQUIRE(!blob->isInBlob(0, 2));
	REQUIRE(!blob->isInBlob(1, 2));
	REQUIRE(!blob->isInBlob(2, 2));
}

TEST_CASE("two blob", "[twoBlob]")
{
	uchar data[] = { 255, 255, 255,
					0, 0, 0,
					255, 255, 255
	};

	cv::Mat test = cv::Mat(3, 3, CV_8UC1, data);

	BlobDetector detector;
	detector.detect(test);

	REQUIRE(detector.numberOfBlobs() == 2);

	std::shared_ptr<Blob> blob;
	blob = detector.getBlob(0);;

	REQUIRE(blob->isInBlob(0, 0));
	REQUIRE(blob->isInBlob(1, 0));
	REQUIRE(blob->isInBlob(2, 0));
	REQUIRE(!blob->isInBlob(0, 1));
	REQUIRE(!blob->isInBlob(1, 1));
	REQUIRE(!blob->isInBlob(2, 1));
	REQUIRE(!blob->isInBlob(0, 2));
	REQUIRE(!blob->isInBlob(1, 2));
	REQUIRE(!blob->isInBlob(2, 2));
	
	blob = detector.getBlob(1);;

	REQUIRE(!blob->isInBlob(0, 0));
	REQUIRE(!blob->isInBlob(1, 0));
	REQUIRE(!blob->isInBlob(2, 0));
	REQUIRE(!blob->isInBlob(0, 1));
	REQUIRE(!blob->isInBlob(1, 1));
	REQUIRE(!blob->isInBlob(2, 1));
	REQUIRE(blob->isInBlob(0, 2));
	REQUIRE(blob->isInBlob(1, 2));
	REQUIRE(blob->isInBlob(2, 2));
}


TEST_CASE("diagonal blob", "[diagonalBlob]")
{
	uchar data[] = { 255, 0, 0,
					0, 255, 0,
					0, 0, 255
	};

	cv::Mat test = cv::Mat(3, 3, CV_8UC1, data);

	BlobDetector detector;
	detector.detect(test);

	REQUIRE(detector.numberOfBlobs() == 1);

	std::shared_ptr<Blob> blob;
	blob = detector.getBlob(0);;

	REQUIRE(blob->isInBlob(0, 0));
	REQUIRE(!blob->isInBlob(1, 0));
	REQUIRE(!blob->isInBlob(2, 0));
	REQUIRE(!blob->isInBlob(0, 1));
	REQUIRE(blob->isInBlob(1, 1));
	REQUIRE(!blob->isInBlob(2, 1));
	REQUIRE(!blob->isInBlob(0, 2));
	REQUIRE(!blob->isInBlob(1, 2));
	REQUIRE(blob->isInBlob(2, 2));
}

TEST_CASE("cross blob", "[crossBlob]")
{
	uchar data[] = { 255, 0, 255,
					0, 255, 0,
					255, 0, 255
	};

	cv::Mat test = cv::Mat(3, 3, CV_8UC1, data);

	BlobDetector detector;
	detector.detect(test);

	REQUIRE(detector.numberOfBlobs() == 1);

	std::shared_ptr<Blob> blob;
	blob = detector.getBlob(0);;

	REQUIRE(blob->isInBlob(0, 0));
	REQUIRE(!blob->isInBlob(1, 0));
	REQUIRE(blob->isInBlob(2, 0));
	REQUIRE(!blob->isInBlob(0, 1));
	REQUIRE(blob->isInBlob(1, 1));
	REQUIRE(!blob->isInBlob(2, 1));
	REQUIRE(blob->isInBlob(0, 2));
	REQUIRE(!blob->isInBlob(1, 2));
	REQUIRE(blob->isInBlob(2, 2));
}

TEST_CASE("no blob", "[noBlob]")
{
	uchar data[] = { 0, 0, 0,
					0, 0, 0,
					0, 0, 0
	};

	cv::Mat test = cv::Mat(3, 3, CV_8UC1, data);

	BlobDetector detector;
	detector.detect(test);

	REQUIRE(detector.numberOfBlobs()  == 0);

}