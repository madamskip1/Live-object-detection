#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch2/catch.hpp"
#include "../GrayscaleConverter.h"

TEST_CASE("Simple grayscale", "[grayscale]")
{
	uchar data[] = { 100, 200, 250,
					0, 0, 0,
					0, 0, 255,
					255, 0, 0,
					0, 255, 255,
					255, 255, 255 };

	cv::Mat test = cv::Mat(6, 1, CV_8UC3, data);

	GrayscaleConverter converter(test);
	converter.convert();

	uchar* resultPtr = converter.getResult().data;

	REQUIRE((int)(*resultPtr++) == 203);
	REQUIRE((int)(*resultPtr++) == 0);
	REQUIRE((int)(*resultPtr++) == 76);
	REQUIRE((int)(*resultPtr++) == 29);
	REQUIRE((int)(*resultPtr++) == 225);
	REQUIRE((int)(*resultPtr++) == 255);
}