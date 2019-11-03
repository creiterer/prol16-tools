/**
 * @author		creiterer
 * @date 		2019-10-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit test of the ArithmeticResult class.
 */

#include "ArithmeticResult.h"

#include <gtest/gtest.h>

using PROL16::util::ArithmeticResult;

TEST(ArithmeticResultTest, test16BitResult) {
	ArithmeticResult const result = 47 * 11;

	ASSERT_EQ(517, result.get());
	ASSERT_EQ(517, result.getLow());
	ASSERT_EQ(0, result.getHigh());

	ASSERT_FALSE(result.isOverflow(16));
	ASSERT_TRUE(result.isOverflow(8));
}

TEST(ArithmeticResultTest, test32BitResult) {
	ArithmeticResult const result = 4711 * 65;

	ASSERT_EQ(306215, result.get());
	ASSERT_EQ(44071, result.getLow());
	ASSERT_EQ(4, result.getHigh());

	ASSERT_FALSE(result.isOverflow(31));
	ASSERT_TRUE(result.isOverflow(16));
	ASSERT_TRUE(result.isOverflow(8));
}
