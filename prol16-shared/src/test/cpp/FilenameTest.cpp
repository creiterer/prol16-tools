/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit test of class Filename.
 */

#include "Filename.h"

#include "gtest/gtest.h"

using util::Filename;

namespace {
	void assertSplitFilename(util::Filename::SplitFilename const &actual, std::string const &expectedPath,
						std::string const &expectedName, std::string const &expectedExtension) {
		std::string actualPath;
		std::string actualName;
		std::string actualExtension;
		std::tie(actualPath, actualName, actualExtension) = actual;

		ASSERT_EQ(expectedPath, actualPath);
		ASSERT_EQ(expectedName, actualName);
		ASSERT_EQ(expectedExtension, actualExtension);
	}
}	// anonymous namespace

TEST(FilenameTest, testOperatorEqualTo) {
	Filename filename("some/path/to/name.extension");
	ASSERT_TRUE(filename == "some/path/to/name.extension");
	ASSERT_TRUE("some/path/to/name.extension" == filename);
	ASSERT_FALSE(filename == "some/path/to/nam.extension");
	ASSERT_FALSE("some/path/to/nam.extension" == filename);
}

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

TEST(FilenameTest, testAppendToName) {
	Filename filename1("");
	ASSERT_EQ("name", filename1.appendToName("name").asString());

	Filename filename2("name");
	ASSERT_EQ("name_suffix", filename2.appendToName("_suffix").asString());

	Filename filename3("name.extension");
	ASSERT_EQ("name_suffix.extension", filename3.appendToName("_suffix").asString());

	Filename filename4("path/name");
	ASSERT_EQ("path/name_suffix", filename4.appendToName("_suffix").asString());

	Filename filename5("path/name.extension");
	ASSERT_EQ("path/name_suffix.extension", filename5.appendToName("_suffix").asString());

	Filename filename6("/some/path/to/name.extension");
	ASSERT_EQ("/some/path/to/name_suffix.extension", filename6.appendToName("_suffix").asString());

	Filename filename7("some/path/");
	ASSERT_EQ("some/path/name", filename7.appendToName("name").asString());

	Filename filename8(".extension");
	ASSERT_EQ("name.extension", filename8.appendToName("name").asString());

	Filename filename9("some/path/.extension");
	ASSERT_EQ("some/path/name.extension", filename9.appendToName("name").asString());

	/// @test const overload
	Filename const constFilename("/some/path/to/name.extension");
	ASSERT_EQ("/some/path/to/name_suffix.extension", constFilename.appendToName("_suffix").asString());
}

TEST(FilenameTest, testSplit) {
	assertSplitFilename(Filename::split(""), "", "", "");

	assertSplitFilename(Filename::split("name"), "", "name", "");
	assertSplitFilename(Filename::split("name.extension"), "", "name", "extension");
	assertSplitFilename(Filename::split("path/name"), "path/", "name", "");
	assertSplitFilename(Filename::split("path/name.extension"), "path/", "name", "extension");
	assertSplitFilename(Filename::split("/some/path/to/name.extension"), "/some/path/to/", "name", "extension");

	assertSplitFilename(Filename::split("some/path/"), "some/path/", "", "");
	assertSplitFilename(Filename::split(".extension"), "", "", "extension");
	assertSplitFilename(Filename::split("some/path/.extension"), "some/path/", "", "extension");
}

TEST(FilenameTest, testGetName) {
	ASSERT_EQ("", Filename::getName(""));
	ASSERT_EQ("", Filename::getName("some/path/"));
	ASSERT_EQ("", Filename::getName(".extension"));
	ASSERT_EQ("", Filename::getName("some/path/.extension"));

	ASSERT_EQ("name", Filename::getName("name"));
	ASSERT_EQ("name", Filename::getName("name.extension"));
	ASSERT_EQ("name", Filename::getName("path/name"));
	ASSERT_EQ("name", Filename::getName("path/name.extension"));
	ASSERT_EQ("name", Filename::getName("/some/path/to/name.extension"));
}

TEST(FilenameTest, testGetExtension) {
	ASSERT_EQ("", Filename::getExtension(""));
	ASSERT_EQ("", Filename::getExtension("some/path/"));
	ASSERT_EQ("", Filename::getExtension("name"));
	ASSERT_EQ("", Filename::getExtension("path/name"));

	ASSERT_EQ("extension", Filename::getExtension("name.extension"));
	ASSERT_EQ("extension", Filename::getExtension("path/name.extension"));
	ASSERT_EQ("extension", Filename::getExtension("/some/path/to/name.extension"));
	ASSERT_EQ("extension", Filename::getExtension(".extension"));
	ASSERT_EQ("extension", Filename::getExtension("some/path/.extension"));
}

TEST(FilenameTest, testGetPath) {
	ASSERT_EQ("", Filename::getPath(""));
	ASSERT_EQ("", Filename::getPath("name"));
	ASSERT_EQ("", Filename::getPath(".extension"));
	ASSERT_EQ("", Filename::getPath("name.extension"));

	ASSERT_EQ("some/path/", Filename::getPath("some/path/"));
	ASSERT_EQ("path/", Filename::getPath("path/name"));
	ASSERT_EQ("path/", Filename::getPath("path/name.extension"));
	ASSERT_EQ("/some/path/to/", Filename::getPath("/some/path/to/name.extension"));
	ASSERT_EQ("some/path/", Filename::getPath("some/path/.extension"));
}
