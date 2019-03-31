/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "CLIArguments.h"

#include "gtest/gtest.h"

#include "CLIError.h"

using namespace util;

TEST(CLIArgumentsTest, testParsingNoArguments) {
	int const argc = 1;
	char const * const argv[] = {"appName"};

	ASSERT_THROW(CLIArguments::parse(argc, argv), CLIError);
}

TEST(CLIArgumentsTest, testParsingPrintToFileValid) {
	int const argc = 2;
	char const * const argv[] = {"appName", "filename"};

	CLIArguments cliArguments = CLIArguments::parse(argc, argv);
	ASSERT_FALSE(cliArguments.shouldPrintToConsole());
	ASSERT_EQ("filename", cliArguments.getFilename());
}

TEST(CLIArgumentsTest, testParsingPrintToFileInvalidFilename) {
	int const argc = 2;
	char const * const argv[] = {"appName", "-c"};

	ASSERT_THROW(CLIArguments::parse(argc, argv), CLIError);
}

TEST(CLIArgumentsTest, testParsingPrintToConsoleValid) {
	int const argc = 3;
	char const * const argv[] = {"appName", "-c", "filename"};

	CLIArguments cliArguments = CLIArguments::parse(argc, argv);
	ASSERT_TRUE(cliArguments.shouldPrintToConsole());
	ASSERT_EQ("filename", cliArguments.getFilename());
}

TEST(CLIArgumentsTest, testParsingPrintToConsoleInvalidOption) {
	int const argc = 3;
	char const * const argv[] = {"appName", "-a", "filename"};

	ASSERT_THROW(CLIArguments::parse(argc, argv), CLIError);
}

TEST(CLIArgumentsTest, testParsingPrintToConsoleInvalidFilename) {
	int const argc = 3;
	char const * const argv[] = {"appName", "-a", "-b"};

	ASSERT_THROW(CLIArguments::parse(argc, argv), CLIError);
}
