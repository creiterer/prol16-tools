/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit tests for math utilities.
 */

#include "MathUtils.h"

#include <stdexcept>

#include "gtest/gtest.h"

using namespace util;

TEST(MathUtilsTest, testIsMultipleOf) {
	ASSERT_TRUE(isMultiple(2, 4));
	ASSERT_TRUE(isMultiple(3, 9));

	ASSERT_FALSE(isMultiple(3, 8));
	ASSERT_FALSE(isMultiple(4, 19));

	ASSERT_THROW(isMultiple(0, 1), std::invalid_argument);
}
