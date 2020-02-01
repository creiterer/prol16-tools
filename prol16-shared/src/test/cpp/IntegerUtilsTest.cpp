/**
 * @author		creiterer
 * @date 		2020-01-15
 * @copyright 	Copyright (c) 2020 Christopher Reiterer
 * @brief 		Unit test of integer utilities.
 */

#include "IntegerUtils.h"

#include <gtest/gtest.h>

using namespace util::integer;

TEST(IntegerUtilsTest, testMergeValues) {
	ASSERT_EQ(0, mergeValues(0, 0));
	ASSERT_EQ(1, mergeValues(0, 1));
	ASSERT_EQ(0xFFFF, mergeValues(0, 0xFFFF));

	ASSERT_EQ(0xFFFF0000, mergeValues(0xFFFF, 0));
	ASSERT_EQ(0xFFFF0001, mergeValues(0xFFFF, 1));
	ASSERT_EQ(0xFFFFFFFF, mergeValues(0xFFFF, 0xFFFF));
}
