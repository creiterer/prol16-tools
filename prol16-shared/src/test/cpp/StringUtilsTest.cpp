/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "StringUtils.h"

#include <string>
#include <stdexcept>

#include "gtest/gtest.h"

using namespace util;

TEST(StringUtilsTest, testCheckStringIsNotEmpty) {
	ASSERT_NO_THROW(preconditions::checkStringIsNotEmpty("foo"));
	ASSERT_NO_THROW(preconditions::checkStringIsNotEmpty(std::string("bar")));

	ASSERT_THROW(preconditions::checkStringIsNotEmpty(""), std::invalid_argument);
	ASSERT_THROW(preconditions::checkStringIsNotEmpty(std::string()), std::invalid_argument);
	ASSERT_THROW(preconditions::checkStringIsNotEmpty(std::string("")), std::invalid_argument);
}

TEST(StringUtilsTest, testToLower) {
	ASSERT_EQ("", toLower(""));
	ASSERT_EQ("lower_case_string", toLower("lower_case_string"));
	ASSERT_EQ("camelcasestring", toLower("CamelCaseString"));
	ASSERT_EQ("upper_case_string", toLower("UPPER_CASE_STRING"));
}

TEST(StringUtilsTest, testPrepend) {
	std::string str("");

	prepend(str, "oo");
	ASSERT_EQ("oo", str);

	prepend(str, 'f');
	ASSERT_EQ("foo", str);

	std::string const str2("oo");
	ASSERT_EQ("foo", prepend(str2, 'f'));
	ASSERT_EQ("toodle-oo", prepend(str2, "toodle-"));

}
