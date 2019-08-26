/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "FileUtils.h"

#include "gtest/gtest.h"

#include <cstdint>
#include <sstream>

using namespace util;

TEST(FileUtilsTest, testReadingEmptyFile) {
	FileBuffer buffer = readEntireFile("resources/empty");
	ASSERT_TRUE(buffer.empty());
}

TEST(FileUtilsTest, testReadingNonEmptyFile) {
	FileBuffer buffer = readEntireFile("resources/alphanumeric");
	ASSERT_STREQ("abcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n0123456789", reinterpret_cast<char*>(buffer.data()));
}

TEST(FileUtilsTest, testReadingBinaryFile) {
	FileBuffer buffer = readEntireFile("resources/binary");
	FileBuffer expectedBuffer = {0xBA, 0xDC, 0x0F, 0xFE, 0xE0, 0xDD, 0xF0, 0x0D};

	ASSERT_EQ(expectedBuffer, buffer);
}

TEST(FileUtilsTest, testWriteValueBinary) {
	std::ostringstream stream;

	writeValueBinary(stream, static_cast<uint16_t>(28));
	std::string const value = stream.str();
	ASSERT_EQ(2, value.size());
	ASSERT_EQ(28, value[0]);
	ASSERT_EQ(0, value[1]);
}
