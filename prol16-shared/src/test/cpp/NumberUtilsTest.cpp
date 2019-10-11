/**
 * @author		creiterer
 * @date 		2019-03-17
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "NumberUtils.h"

#include "gtest/gtest.h"

using namespace PROL16::util;

TEST(NumberUtilsTest, testParseNumber) {
	ASSERT_EQ(42405, parseNumber("42405"));
	ASSERT_EQ(42405, parseNumber("42405d"));
	ASSERT_EQ(42405, parseNumber("A5A5h"));
	ASSERT_EQ(42405, parseNumber("1010010110100101b"));

	ASSERT_EQ(42405, parseNumber("42_405"));
	ASSERT_EQ(42405, parseNumber("42_405d"));
	ASSERT_EQ(42405, parseNumber("A5_A5h"));
	ASSERT_EQ(42405, parseNumber("1010_0101_1010_0101b"));
}

TEST(NumberUtilsTest, testFormatAsHexNumberWithBase) {
	ASSERT_EQ("0x0000", formatAsHexNumberWithBase(0));
	ASSERT_EQ("0x000F", formatAsHexNumberWithBase(0xF));
	ASSERT_EQ("0xFFFF", formatAsHexNumberWithBase(0xFFFF));
}
