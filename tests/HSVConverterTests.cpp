#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch2/catch.hpp"
#include "../BGRToHSVConverter.h"

TEST_CASE("simple HSV", "[hsv]")
{
	uchar data[] = { 100, 200, 250,
					0, 0, 0,
					0, 0, 255,
					255, 0, 0,
					0, 255, 255,
					255, 255, 255 };

	cv::Mat test = cv::Mat(6, 1, CV_8UC3, data);

	BGRToHSVConverter converter(test);
	converter.convert();

	uchar* resultPtr = converter.getResult().data;

	// 100, 200, 250
	{
		REQUIRE((int)(*resultPtr++) == 20);
		REQUIRE((int)(*resultPtr++) == 153);
		REQUIRE(((int)(*resultPtr++) == 250 || (int)(*resultPtr) == 249));
	}

	// 0, 0, 0
	{
		REQUIRE((int)(*resultPtr++) == 0);
		REQUIRE((int)(*resultPtr++) == 0);
		REQUIRE((int)(*resultPtr++) == 0);
	}

	// 0, 0, 225
	{
		REQUIRE((int)(*resultPtr++) == 0);
		REQUIRE((int)(*resultPtr++) == 255);
		REQUIRE((int)(*resultPtr++) == 255);
	}

	// 255, 0, 0
	{
		REQUIRE((int)(*resultPtr++) == 120);
		REQUIRE((int)(*resultPtr++) == 255);
		REQUIRE((int)(*resultPtr++) == 255);
	}

	// 0, 255, 255
	{
		REQUIRE((int)(*resultPtr++) == 30);
		REQUIRE((int)(*resultPtr++) == 255);
		REQUIRE((int)(*resultPtr++) == 255);
	}

	// 255, 255, 255
	{
		REQUIRE((int)(*resultPtr++) == 0);
		REQUIRE((int)(*resultPtr++) == 0);
		REQUIRE((int)(*resultPtr++) == 255);
	}
}