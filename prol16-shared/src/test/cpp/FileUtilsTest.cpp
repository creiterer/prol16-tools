/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit tests for file utilities.
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
	ASSERT_EQ("abcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n0123456789", getBufferAsString(buffer));
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

TEST(FileUtilsTest, testReadValue) {
	FileBuffer buffer{28, 0, 255, 0};

	uint16_t value = readValue<uint16_t>(buffer);
	ASSERT_EQ(28, value);

	value = readValue<uint16_t>(buffer, 2);
	ASSERT_EQ(255, value);
}

TEST(FileUtilsTest, testWriteBufferToStream) {
	std::ostringstream stream;
	Buffer<uint16_t> buffer{0xCAFE, 0xBABE, 0xDEAD, 0xD0DE};

	writeBufferToStream(stream, buffer);

	std::string const streamBuffer = stream.str();
	ASSERT_EQ(buffer.size() * sizeof(uint16_t)/sizeof(char), streamBuffer.size());
	ASSERT_EQ(0xFE, static_cast<uint8_t>(streamBuffer[0]));
	ASSERT_EQ(0xCA, static_cast<uint8_t>(streamBuffer[1]));
	ASSERT_EQ(0xBE, static_cast<uint8_t>(streamBuffer[2]));
	ASSERT_EQ(0xBA, static_cast<uint8_t>(streamBuffer[3]));
	ASSERT_EQ(0xAD, static_cast<uint8_t>(streamBuffer[4]));
	ASSERT_EQ(0xDE, static_cast<uint8_t>(streamBuffer[5]));
	ASSERT_EQ(0xDE, static_cast<uint8_t>(streamBuffer[6]));
	ASSERT_EQ(0xD0, static_cast<uint8_t>(streamBuffer[7]));
}

TEST(FileUtilsTest, testWriteStringToStream) {
	std::ostringstream stream;
	std::string const str = "some string";

	writeStringToStream(stream, str);

	ASSERT_STREQ("some string", stream.str().c_str());
}
