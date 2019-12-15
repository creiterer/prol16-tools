/**
 * @author		creiterer
 * @date 		2019-12-03
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit tests for stream utilities.
 */

#include "StreamUtils.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(StreamUtilsTest, testInsertionOperator) {
	std::vector<int> const empty;
	std::ostringstream stream1;
	stream1 << empty;
	ASSERT_EQ("{}", stream1.str());

	std::vector<int> const oneValue{7};
	std::ostringstream stream2;
	stream2 << oneValue;
	ASSERT_EQ("{7}", stream2.str());

	std::vector<int> const intValues{0, 1, 2, 3, 4};
	std::ostringstream stream3;
	stream3 << intValues;
	ASSERT_EQ("{0, 1, 2, 3, 4}", stream3.str());

	std::vector<std::string> stringValues{"bli", "bla", "blup"};
	std::ostringstream stream4;
	stream4 << stringValues;
	ASSERT_EQ("{bli, bla, blup}", stream4.str());
}
