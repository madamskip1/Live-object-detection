#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch2/catch.hpp"
#include "../FilterImage.h"

TEST_CASE("do nothing kernel", "[nothing]")
{
	uchar data[] = { 100, 200, 250,
					0, 100, 0,
					50, 0, 255,
					255, 60, 200 };

	cv::Mat test = cv::Mat(4, 1, CV_8UC3, data);

	float kernel[] = { 0, 0, 0,
						0, 1, 0,
						0, 0, 0 };

	FilterImage filter(test);
	filter.setKernel(kernel, 3);
	filter.filter();
	uchar* resultPtr = filter.getResult().data;

	REQUIRE((int)(*resultPtr++) == 100);
	REQUIRE((int)(*resultPtr++) == 200);
	REQUIRE((int)(*resultPtr++) == 250);

	REQUIRE((int)(*resultPtr++) == 0);
	REQUIRE((int)(*resultPtr++) == 100);
	REQUIRE((int)(*resultPtr++) == 0);

	REQUIRE((int)(*resultPtr++) == 50);
	REQUIRE((int)(*resultPtr++) == 0);
	REQUIRE((int)(*resultPtr++) == 255);

	REQUIRE((int)(*resultPtr++) == 255);
	REQUIRE((int)(*resultPtr++) == 60);
	REQUIRE((int)(*resultPtr++) == 200);
}

TEST_CASE("box blur 3x3", "[boxblur]")
{
	uchar data[] = { 100, 200, 250,	0, 100, 0,		50, 0, 255,
					255, 60, 200,	50, 0, 255,		255, 60, 200, 
					0, 100, 0,		255, 60, 200,	100, 200, 250, };

	cv::Mat test = cv::Mat(3, 3, CV_8UC3, data);

	float kernel[] = { 1.0f / 9, 1.0f / 9, 1.0f / 9,
						1.0f / 9, 1.0f / 9, 1.0f / 9,
						1.0f / 9, 1.0f / 9, 1.0f / 9 };

	FilterImage filter(test);
	filter.setKernel(kernel, 3);
	filter.filter();
	uchar* resultPtr = filter.getResult().ptr<uchar>(0);

	REQUIRE((int)resultPtr[0] == 45);
	REQUIRE((int)resultPtr[1] == 40);
	REQUIRE((int)resultPtr[2] == 78);

	REQUIRE((int)resultPtr[3] == 78);
	REQUIRE((int)resultPtr[4] == 46);
	REQUIRE((int)resultPtr[5] == 128);

	REQUIRE((int)resultPtr[6] == 39);
	REQUIRE((int)resultPtr[7] == 17);
	REQUIRE((int)resultPtr[8] == 78);

	resultPtr = filter.getResult().ptr<uchar>(1);
	REQUIRE((int)resultPtr[3] == 118);
	REQUIRE((int)resultPtr[4] == 86);
	REQUIRE((int)resultPtr[5] == 178);

	resultPtr = filter.getResult().ptr<uchar>(2);
	REQUIRE((int)resultPtr[6] == 73);
	REQUIRE((int)resultPtr[7] == 35);
	REQUIRE((int)resultPtr[8] == 100);
}

TEST_CASE("Dilata", "[boxblur]")
{
	uchar data[] = { 255,  0,	 0,	 0,	 255,
					   0,  0,	 0,  0,	 0,	
					   0,  255,  0,	 0,	 0 };

	cv::Mat test = cv::Mat(3, 5, CV_8UC1, data);

	float kernel[] = { 1, 1, 1,
						1, 1, 1,
						1, 1, 1. };

	FilterImage filter(test);
	filter.setKernel(kernel, 3);
	filter.filter();
	uchar* resultPtr = filter.getResult().ptr<uchar>(0);

	REQUIRE((int)resultPtr[0] == 255);
	REQUIRE((int)resultPtr[1] == 255);
	REQUIRE((int)resultPtr[2] == 0);
	REQUIRE((int)resultPtr[3] == 255);
	REQUIRE((int)resultPtr[4] == 255);

	resultPtr = filter.getResult().ptr<uchar>(1);

	REQUIRE((int)resultPtr[0] == 255);
	REQUIRE((int)resultPtr[1] == 255);
	REQUIRE((int)resultPtr[2] == 255);
	REQUIRE((int)resultPtr[3] == 255);
	REQUIRE((int)resultPtr[4] == 255);

	resultPtr = filter.getResult().ptr<uchar>(2);

	REQUIRE((int)resultPtr[0] == 255);
	REQUIRE((int)resultPtr[1] == 255);
	REQUIRE((int)resultPtr[2] == 255);
	REQUIRE((int)resultPtr[3] == 0);
	REQUIRE((int)resultPtr[4] == 0);
}