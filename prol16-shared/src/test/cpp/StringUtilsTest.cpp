/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "StringUtils.h"

#include "gtest/gtest.h"

using util::toLower;

TEST(StringUtilsTest, testToLower) {
	ASSERT_EQ("", toLower(""));
	ASSERT_EQ("lower_case_string", toLower("lower_case_string"));
	ASSERT_EQ("camelcasestring", toLower("CamelCaseString"));
	ASSERT_EQ("upper_case_string", toLower("UPPER_CASE_STRING"));
}

