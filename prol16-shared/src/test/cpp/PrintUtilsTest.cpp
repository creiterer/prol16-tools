/**
 * @author		creiterer
 * @date 		2019-10-27
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "PrintUtils.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <sstream>

using namespace util;

TEST(PrintUtilsTest, testFormattedHexNumberPrinting) {
	uint16_t const value1 = 0xFFFF;

	std::ostringstream stream1;
	printHexNumberFormatted(stream1, value1);
	ASSERT_EQ("FFFF", stream1.str());

	std::ostringstream stream2;
	printHexNumberFormattedWithBase(stream2, value1);
	ASSERT_EQ("0xFFFF", stream2.str());

	uint32_t const value2 = 0xFFFF'FFFF;

	std::ostringstream stream3;
	printHexNumberFormatted(stream3, value2);
	ASSERT_EQ("FFFFFFFF", stream3.str());

	std::ostringstream stream4;
	printHexNumberFormattedWithBase(stream4, value2);
	ASSERT_EQ("0xFFFFFFFF", stream4.str());
}

