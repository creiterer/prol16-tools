/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit test of class Filename.
 */

#include "Filename.h"

#include "gtest/gtest.h"

using util::Filename;

TEST(FilenameTest, testStringConversion) {
	Filename filename("some/path/to/name.extension");
	ASSERT_EQ("some/path/to/name.extension", filename.asString());
	ASSERT_EQ("some/path/to/name.extension", static_cast<std::string>(filename));
}

TEST(FilenameTest, testGetWithoutExtension) {
	Filename filename1("name.extension");
	ASSERT_EQ("name", filename1.getWithoutExtension());

	Filename filename2("name");
	ASSERT_EQ("name", filename2.getWithoutExtension());

	Filename filename3("some/path/to/name.extension");
	ASSERT_EQ("some/path/to/name", filename3.getWithoutExtension());

	Filename filename4("./some/path/to/name.extension");
	ASSERT_EQ("./some/path/to/name", filename4.getWithoutExtension());

	Filename filename5("./some/../to/name.extension");
	ASSERT_EQ("./some/../to/name", filename5.getWithoutExtension());

	Filename filename6("./some/../to/name");
	ASSERT_EQ("./some/../to/name", filename6.getWithoutExtension());
}

TEST(FilenameTest, testGetWithCustomExtension) {
	Filename filename1("name.extension");
	ASSERT_EQ("name.customExtension", filename1.getWithCustomExtension("customExtension"));

	Filename filename2("name");
	ASSERT_EQ("name.customExtension", filename2.getWithCustomExtension("customExtension"));

	Filename filename3("some/path/to/name.extension");
	ASSERT_EQ("some/path/to/name.customExtension", filename3.getWithCustomExtension("customExtension"));

	Filename filename4("./some/path/to/name.extension");
	ASSERT_EQ("./some/path/to/name.customExtension", filename4.getWithCustomExtension("customExtension"));

	Filename filename5("./some/../to/name.extension");
	ASSERT_EQ("./some/../to/name.customExtension", filename5.getWithCustomExtension("customExtension"));

	Filename filename6("./some/../to/name");
	ASSERT_EQ("./some/../to/name.customExtension", filename6.getWithCustomExtension("customExtension"));
}
