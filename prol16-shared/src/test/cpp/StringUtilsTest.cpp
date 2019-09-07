/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "StringUtils.h"

#include <cstdint>
#include <string>
#include <stdexcept>
#include <vector>

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

TEST(StringUtilsTest, testEncode) {
	std::string str("abc");

	std::vector<uint16_t> buffer = encode<uint16_t>(str);
	ASSERT_EQ(2, buffer.size());
	ASSERT_EQ(('b' << 8) + 'a', buffer[0]);
	ASSERT_EQ('c', buffer[1]);
}

TEST(StringUtilsTest, testLTrim) {
	std::string str;

	ltrim(str, " \t");
	ASSERT_TRUE(str.empty());

	str = "test";
	ltrim(str, " \t");
	ASSERT_EQ("test", str);

	str = " test";
	ltrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\ttest";
	ltrim(str, " \t");
	ASSERT_EQ("test", str);

	str = " \ttest";
	ltrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\t test";
	ltrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "test \t";
	ltrim(str, " \t");
	ASSERT_EQ("test \t", str);

	str = "\t test \t";
	ltrim(str, " \t");
	ASSERT_EQ("test \t", str);

	str = "\t \t\t test";
	ltrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\t t est";
	ltrim(str, " \t");
	ASSERT_EQ("t est", str);

	str = "\t \t";
	ltrim(str, " \t");
	ASSERT_TRUE(str.empty());
}

TEST(StringUtilsTest, testRTrim) {
	std::string str;

	rtrim(str, " \t");
	ASSERT_TRUE(str.empty());

	str = "test";
	rtrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "test ";
	rtrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "test\t";
	rtrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "test \t";
	rtrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "test\t ";
	rtrim(str, " \t");
	ASSERT_EQ("test", str);

	str = " \ttest";
	rtrim(str, " \t");
	ASSERT_EQ(" \ttest", str);

	str = "\t test \t";
	rtrim(str, " \t");
	ASSERT_EQ("\t test", str);

	str = "test\t \t\t ";
	rtrim(str, " \t");
	ASSERT_EQ("test", str);

	str = "tes t\t ";
	rtrim(str, " \t");
	ASSERT_EQ("tes t", str);

	str = "\t \t";
	rtrim(str, " \t");
	ASSERT_TRUE(str.empty());
}

TEST(StringUtilsTest, testTrim) {
	std::string str;

	trim(str, " \t");
	ASSERT_TRUE(str.empty());

	str = "test";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = " test";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "test ";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = " test ";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\ttest";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "test\t";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\ttest\t";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\t test";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "test \t";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\t test \t";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\t \t test\t \t\t ";
	trim(str, " \t");
	ASSERT_EQ("test", str);

	str = "\t t es t\t ";
	trim(str, " \t");
	ASSERT_EQ("t es t", str);

	str = "\t \t";
	trim(str, " \t");
	ASSERT_TRUE(str.empty());
}

TEST(StringUtilsTest, testTrimQuotes) {
	std::string str;
	trimQuotes(str);
	ASSERT_TRUE(str.empty());

	str = "test";
	trimQuotes(str);
	ASSERT_EQ("test", str);

	str = "\"test\"";
	trimQuotes(str);
	ASSERT_EQ("test", str);
}

TEST(StringUtilsTest, testGetUnquoted) {
	std::string str;
	ASSERT_TRUE(getUnquoted(str).empty());

	str = "test";
	ASSERT_EQ("test", getUnquoted(str));

	str = "\"test\"";
	ASSERT_EQ("test", getUnquoted(str));
}
