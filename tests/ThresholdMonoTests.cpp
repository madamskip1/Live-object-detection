#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "..\ThresholdColor.h"


TEST_CASE("3 depth", "[3depthchannels]")
{
		uchar data[] = { 100, 200, 250,	0, 100, 0,		50, 0, 255,
						255, 60, 200,	50, 0, 255,		255, 60, 200, 
						0, 100, 0,		255, 60, 200,	100, 200, 250, };
	
		cv::Mat test = cv::Mat(3, 3, CV_8UC3, data);

	ThresholdColorMono threshold(test);

	threshold.setColor(1, 0, 100);
	threshold.setColor(2, 0, 70);
	threshold.setColor(3, 240, 255);
	threshold.filter();


	uchar* resultPtr = threshold.getResult().ptr<uchar>(0);

	REQUIRE((int)resultPtr[0] == 0);
	REQUIRE((int)resultPtr[1] == 0);
	REQUIRE((int)resultPtr[2] == 255);

	resultPtr = threshold.getResult().ptr<uchar>(1);

	REQUIRE((int)resultPtr[0] == 0);
	REQUIRE((int)resultPtr[1] == 255);
	REQUIRE((int)resultPtr[2] == 0);

	resultPtr = threshold.getResult().ptr<uchar>(2);

	REQUIRE((int)resultPtr[0] == 0);
	REQUIRE((int)resultPtr[1] == 0);
	REQUIRE((int)resultPtr[2] == 0);
}

TEST_CASE("1 depth", "[1depthchannel]")
{
	uchar data[] = { 100, 200, 250,
					255, 60, 200,
					0, 100, 0,
	};

	cv::Mat test = cv::Mat(3, 3, CV_8UC1, data);

	ThresholdColorMono threshold(test);

	threshold.setColor(1, 100, 200);
	threshold.filter();


	uchar* resultPtr = threshold.getResult().ptr<uchar>(0);

	REQUIRE((int)resultPtr[0] == 255);
	REQUIRE((int)resultPtr[1] == 255);
	REQUIRE((int)resultPtr[2] == 0);

	resultPtr = threshold.getResult().ptr<uchar>(1);

	REQUIRE((int)resultPtr[0] == 0);
	REQUIRE((int)resultPtr[1] == 0);
	REQUIRE((int)resultPtr[2] == 255);

	resultPtr = threshold.getResult().ptr<uchar>(2);

	REQUIRE((int)resultPtr[0] == 0);
	REQUIRE((int)resultPtr[1] == 255);
	REQUIRE((int)resultPtr[2] == 0);
}