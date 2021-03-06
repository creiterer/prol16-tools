/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit tests for string utilities.
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

TEST(StringUtilsTest, testToUpper) {
	ASSERT_EQ("", toUpper(""));
	ASSERT_EQ("LOWER_CASE_STRING", toUpper("lower_case_string"));
	ASSERT_EQ("CAMELCASESTRING", toUpper("CamelCaseString"));
	ASSERT_EQ("UPPER_CASE_STRING", toUpper("UPPER_CASE_STRING"));
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

	str = "\"\\n\"";
	buffer = encode<uint16_t>(str);
	ASSERT_EQ(3, buffer.size());
	ASSERT_EQ(('\\' << 8) + '"', buffer[0]);
	ASSERT_EQ(('"' << 8) + 'n', buffer[1]);
	ASSERT_EQ(0, buffer[2]);
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

TEST(StringUtilsTest, testGetQuoted) {
	ASSERT_EQ("\"\"", getQuoted(""));
	ASSERT_EQ("\"test\"", getQuoted("test"));
	ASSERT_EQ("'c'", getQuoted('c'));
}

TEST(StringUtilsTest, testHandleEscapeSequences) {
	std::string str;
	ASSERT_TRUE(handleEscapeSequences(str).empty());

	str = "test";
	ASSERT_EQ("test", handleEscapeSequences(str));

	str = "\n";
	ASSERT_EQ("\n", handleEscapeSequences(str));

	str = "\\n";
	ASSERT_EQ("\n", handleEscapeSequences(str));

	str = "\\";
	ASSERT_EQ("\\", handleEscapeSequences(str));

	str = "test\n";
	ASSERT_EQ("test\n", handleEscapeSequences(str));

	str = "test\\n";
	ASSERT_EQ("test\n", handleEscapeSequences(str));

	str = "\\ntest\\n";
	ASSERT_EQ("\ntest\n", handleEscapeSequences(str));

	str = "\\ttest\\t";
	ASSERT_EQ("\ttest\t", handleEscapeSequences(str));

	str = "\\rtest\\r";
	ASSERT_EQ("\rtest\r", handleEscapeSequences(str));
}

TEST(StringUtilsTest, testFormat) {
	ASSERT_EQ("", format(""));
	ASSERT_EQ("test", format("test"));
	ASSERT_EQ("test", format("%s", "test"));
	ASSERT_EQ("prefix data suffix", format("prefix %s suffix", "data"));
	ASSERT_EQ("some value = 2", format("some value = %d", 2));
}

TEST(StringUtilsTest, testFormatHexNumbers) {
	ASSERT_EQ("0x00", formatAsHexNumberWithBase(static_cast<uint8_t>(0)));
	ASSERT_EQ("00", formatAsHexNumber(static_cast<uint8_t>(0)));

	ASSERT_EQ("0x0F", formatAsHexNumberWithBase(static_cast<uint8_t>(0xF)));
	ASSERT_EQ("0F", formatAsHexNumber(static_cast<uint8_t>(0xF)));

	ASSERT_EQ("0xFF", formatAsHexNumberWithBase(static_cast<uint8_t>(0xFF)));
	ASSERT_EQ("FF", formatAsHexNumber(static_cast<uint8_t>(0xFF)));

	ASSERT_EQ("0x0000", formatAsHexNumberWithBase(static_cast<uint16_t>(0)));
	ASSERT_EQ("0000", formatAsHexNumber(static_cast<uint16_t>(0)));

	ASSERT_EQ("0x000F", formatAsHexNumberWithBase(static_cast<uint16_t>(0xF)));
	ASSERT_EQ("000F", formatAsHexNumber(static_cast<uint16_t>(0xF)));

	ASSERT_EQ("0xFFFF", formatAsHexNumberWithBase(static_cast<uint16_t>(0xFFFF)));
	ASSERT_EQ("FFFF", formatAsHexNumber(static_cast<uint16_t>(0xFFFF)));

	ASSERT_EQ("0x00000000", formatAsHexNumberWithBase(0));
	ASSERT_EQ("00000000", formatAsHexNumber(0));

	ASSERT_EQ("0x0000000F", formatAsHexNumberWithBase(0xF));
	ASSERT_EQ("0000000F", formatAsHexNumber(0xF));

	ASSERT_EQ("0x0000FFFF", formatAsHexNumberWithBase(0xFFFF));
	ASSERT_EQ("0000FFFF", formatAsHexNumber(0xFFFF));

	ASSERT_EQ("0xFFFFFFFF", formatAsHexNumberWithBase(0xFFFFFFFF));
	ASSERT_EQ("FFFFFFFF", formatAsHexNumber(0xFFFFFFFF));
}

TEST(StringUtilsTest, testGetPadded) {
	std::string const str("test");
	ASSERT_EQ(5, getPadded(str, 1).size() + 1);

	std::string const padded2 = getPadded(str, 2);
	ASSERT_EQ(6, padded2.size() + 1);
	ASSERT_EQ('\0', padded2[5]);

	std::string const padded3 = getPadded(str, 3);
	ASSERT_EQ(6, padded3.size() + 1);
	ASSERT_EQ('\0', padded3[5]);

	std::string const padded4 = getPadded(str, 4);
	ASSERT_EQ(8, padded4.size() + 1);
	ASSERT_EQ('\0', padded4[5]);
	ASSERT_EQ('\0', padded4[6]);
	ASSERT_EQ('\0', padded4[7]);
}

TEST(StringUtilsTest, testGetEscaped) {
	ASSERT_EQ("", getEscaped(""));
	ASSERT_EQ("test", getEscaped("test"));
	ASSERT_EQ("test\\n", getEscaped("test\n"));
	ASSERT_EQ("\\ntest", getEscaped("\ntest"));
	ASSERT_EQ("\\nte\\rst\\t", getEscaped("\nte\rst\t"));
	ASSERT_EQ("\\n\\r\\t", getEscaped("\n\r\t"));
}
