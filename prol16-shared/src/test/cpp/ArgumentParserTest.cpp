/**
 * @author		creiterer
 * @date 		2019-08-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "ArgumentParser.h"

#include <gtest/gtest.h>

#include "CLIError.h"
#include "CLIArguments.h"

using namespace util::cli;

TEST(ArgumentParserTest, testOnePositionalArgument) {
	ArgumentParser argumentParser;
	argumentParser.addPositionalArgument("filename");

	int const argc = 2;
	char const * const argv[] = {"appName", "some_file_name.txt"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_EQ("some_file_name.txt", cliArguments["filename"]);
}

TEST(ArgumentParserTest, testMultiplePositionalArguments) {
	ArgumentParser argumentParser;
	argumentParser.addPositionalArgument("source").addPositionalArgument("destination");

	int const argc = 3;
	char const * const argv[] = {"appName", "path/to/source/dir", "path/to/dest/dir"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_EQ("path/to/source/dir", cliArguments["source"]);
	ASSERT_EQ("path/to/dest/dir", cliArguments["destination"]);
}

TEST(ArgumentParserTest, testPositionalArgumentsNotSatisfied) {
	ArgumentParser argumentParser;
	argumentParser.addPositionalArgument("filename");

	int const argc = 1;
	char const * const argv[] = {"appName"};

	ASSERT_THROW(argumentParser.parseArguments(argc, argv), CLIError);
}

TEST(ArgumentParserTest, testOneOptionalArgumentWithLongNameOnly) {
	ArgumentParser argumentParser;
	argumentParser.addOptionalArgument("--verbosity", "1");

	int const argc = 3;
	char const * const argv[] = {"appName", "--verbosity", "2"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_EQ("2", cliArguments["--verbosity"]);
}

TEST(ArgumentParserTest, testOneOptionalArgumentWithShortAndLongName) {
	ArgumentParser argumentParser;
	argumentParser.addOptionalArgument("-v", "--verbosity", "1");

	int const argc = 3;

	char const * const argvWithShortName[] = {"appName", "-v", "2"};
	CLIArguments cliArguments = argumentParser.parseArguments(argc, argvWithShortName);
	ASSERT_EQ("2", cliArguments["-v"]);
	ASSERT_EQ("2", cliArguments["--verbosity"]);

	char const * const argvWithLongName[] = {"appName", "--verbosity", "3"};
	CLIArguments cliArguments2 = argumentParser.parseArguments(argc, argvWithLongName);
	ASSERT_EQ("3", cliArguments2["-v"]);
	ASSERT_EQ("3", cliArguments2["--verbosity"]);
}

TEST(ArgumentParserTest, testMultipleOptionalArgumentsWithLongNameOnly) {
	ArgumentParser argumentParser;
	argumentParser.addOptionalArgument("--source", "./").addOptionalArgument("--dest", "./");

	int const argc = 5;
	char const * const argv[] = {"appName", "--dest", "path/to/dest", "--source", "path/to/source"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_EQ("path/to/source", cliArguments["--source"]);
	ASSERT_EQ("path/to/dest", cliArguments["--dest"]);
}

TEST(ArgumentParserTest, testMultipleOptionalArgumentsWithShortAndLongNamesMixed) {
	ArgumentParser argumentParser;
	argumentParser.addOptionalArgument("-s", "--source", "./").addOptionalArgument("-d", "--dest", "./");

	int const argc = 5;

	char const * const argvWithLongNamesOnly[] = {"appName", "--dest", "path/to/dest/1", "--source", "path/to/source/1"};
	CLIArguments cliArguments = argumentParser.parseArguments(argc, argvWithLongNamesOnly);
	ASSERT_EQ("path/to/source/1", cliArguments["-s"]);
	ASSERT_EQ("path/to/source/1", cliArguments["--source"]);
	ASSERT_EQ("path/to/dest/1", cliArguments["-d"]);
	ASSERT_EQ("path/to/dest/1", cliArguments["--dest"]);

	char const * const argvWithShortNamesOnly[] = {"appName", "-d", "path/to/dest/2", "-s", "path/to/source/2"};
	CLIArguments cliArguments2 = argumentParser.parseArguments(argc, argvWithShortNamesOnly);
	ASSERT_EQ("path/to/source/2", cliArguments2["-s"]);
	ASSERT_EQ("path/to/source/2", cliArguments2["--source"]);
	ASSERT_EQ("path/to/dest/2", cliArguments2["-d"]);
	ASSERT_EQ("path/to/dest/2", cliArguments2["--dest"]);

	char const * const argvWithShortAndLongNamesMixed[] = {"appName", "--dest", "path/to/dest/3", "-s", "path/to/source/3"};
	CLIArguments cliArguments3 = argumentParser.parseArguments(argc, argvWithShortAndLongNamesMixed);
	ASSERT_EQ("path/to/source/3", cliArguments3["-s"]);
	ASSERT_EQ("path/to/source/3", cliArguments3["--source"]);
	ASSERT_EQ("path/to/dest/3", cliArguments3["-d"]);
	ASSERT_EQ("path/to/dest/3", cliArguments3["--dest"]);
}

TEST(ArgumentParserTest, testNotSpecifiedOptionalArguments) {
	ArgumentParser argumentParser;
	argumentParser.addOptionalArgument("-v", "--verbosity", "1");

	int const argc = 1;
	char const * const argv[] = {"appName"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_EQ("1", cliArguments["-v"]);
	ASSERT_EQ("1", cliArguments["--verbosity"]);
}

TEST(ArgumentParserTest, testNotAllOptionalArgumentsSpecified) {
	ArgumentParser argumentParser;
	argumentParser.addOptionalArgument("-s", "--source", "./").addOptionalArgument("-d", "--dest", "./");

	int const argc = 3;
	char const * const argv[] = {"appName", "-d", "path/to/dest"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_EQ("./", cliArguments["-s"]);
	ASSERT_EQ("./", cliArguments["--source"]);
	ASSERT_EQ("path/to/dest", cliArguments["-d"]);
	ASSERT_EQ("path/to/dest", cliArguments["--dest"]);
}

TEST(ArgumentParserTest, testOptionalArgumentWithoutSpecifiedValue) {
	ArgumentParser argumentParser;
	argumentParser.addOptionalArgument("-v", "--verbosity", "1");

	int const argc = 2;

	char const * const argvWithShortName[] = {"appName", "-v"};
	ASSERT_THROW(argumentParser.parseArguments(argc, argvWithShortName), CLIError);

	char const * const argvWithLongName[] = {"appName", "--verbosity"};
	ASSERT_THROW(argumentParser.parseArguments(argc, argvWithLongName), CLIError);
}

TEST(ArgumentParserTest, testOneFlagWithLongNameOnly) {
	ArgumentParser argumentParser;
	argumentParser.addFlag("--verbose", false);

	int const argc = 2;
	char const * const argv[] = {"appName", "--verbose"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_TRUE(cliArguments.isSet("--verbose"));
}

TEST(ArgumentParserTest, testOneFlagWithShortAndLongName) {
	ArgumentParser argumentParser;
	argumentParser.addFlag("-v", "--verbose", false);

	int const argc = 2;

	char const * const argvWithShortName[] = {"appName", "-v"};
	CLIArguments cliArguments = argumentParser.parseArguments(argc, argvWithShortName);
	ASSERT_TRUE(cliArguments.isSet("-v"));
	ASSERT_TRUE(cliArguments.isSet("--verbose"));

	char const * const argvWithLongName[] = {"appName", "--verbose"};
	CLIArguments cliArguments2 = argumentParser.parseArguments(argc, argvWithLongName);
	ASSERT_TRUE(cliArguments2.isSet("-v"));
	ASSERT_TRUE(cliArguments2.isSet("--verbose"));
}

TEST(ArgumentParserTest, testMultipleFlagsWithLongNameOnly) {
	ArgumentParser argumentParser;
	argumentParser.addFlag("--all", false).addFlag("--long", false);

	int const argc = 3;
	char const * const argv[] = {"appName", "--long", "--all"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_TRUE(cliArguments.isSet("--all"));
	ASSERT_TRUE(cliArguments.isSet("--long"));
}

TEST(ArgumentParserTest, testMultipleFlagsWithShortAndLongNamesMixed) {
	ArgumentParser argumentParser;
	argumentParser.addFlag("-a", "--all", false).addFlag("-l", "--long", false);

	int const argc = 3;

	char const * const argvWithLongNamesOnly[] = {"appName", "--long", "--all"};
	CLIArguments cliArguments = argumentParser.parseArguments(argc, argvWithLongNamesOnly);
	ASSERT_TRUE(cliArguments.isSet("-l"));
	ASSERT_TRUE(cliArguments.isSet("--long"));
	ASSERT_TRUE(cliArguments.isSet("-a"));
	ASSERT_TRUE(cliArguments.isSet("--all"));

	char const * const argvWithShortNamesOnly[] = {"appName", "-l", "-a"};
	CLIArguments cliArguments2 = argumentParser.parseArguments(argc, argvWithShortNamesOnly);
	ASSERT_TRUE(cliArguments2.isSet("-l"));
	ASSERT_TRUE(cliArguments2.isSet("--long"));
	ASSERT_TRUE(cliArguments2.isSet("-a"));
	ASSERT_TRUE(cliArguments2.isSet("--all"));

	char const * const argvWithShortAndLongNamesMixed[] = {"appName", "--all", "-l"};
	CLIArguments cliArguments3 = argumentParser.parseArguments(argc, argvWithShortAndLongNamesMixed);
	ASSERT_TRUE(cliArguments3.isSet("-l"));
	ASSERT_TRUE(cliArguments3.isSet("--long"));
	ASSERT_TRUE(cliArguments3.isSet("-a"));
	ASSERT_TRUE(cliArguments3.isSet("--all"));
}

TEST(ArgumentParserTest, testNotSpecifiedFlags) {
	ArgumentParser argumentParser;
	argumentParser.addFlag("-v", "--verbose", false);

	int const argc = 1;
	char const * const argv[] = {"appName"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_FALSE(cliArguments.isSet("-v"));
	ASSERT_FALSE(cliArguments.isSet("--verbose"));
}

TEST(ArgumentParserTest, testNotAllFlagsSpecified) {
	ArgumentParser argumentParser;
	argumentParser.addFlag("-a", "--all", false).addFlag("-l", "--long", false);

	int const argc = 2;
	char const * const argv[] = {"appName", "-l"};

	CLIArguments cliArguments = argumentParser.parseArguments(argc, argv);
	ASSERT_TRUE(cliArguments.isSet("-l"));
	ASSERT_TRUE(cliArguments.isSet("--long"));
	ASSERT_FALSE(cliArguments.isSet("-a"));
	ASSERT_FALSE(cliArguments.isSet("--all"));
}

TEST(ArgumentParserTest, testAllArgumentVariantsCombined) {
	ArgumentParser argumentParser;
	argumentParser.addPositionalArgument("filename");
	argumentParser.addOptionalArgument("-s", "--sourcedir", "./").addOptionalArgument("-d", "--destdir", "./");
	argumentParser.addFlag("-v", "--verbose", false).addFlag("-l", "--followLinks", false);

	int argc = 2;
	char const * const argvFilenameOnly[] = {"appName", "some_file.txt"};
	CLIArguments cliArguments = argumentParser.parseArguments(argc, argvFilenameOnly);
	ASSERT_EQ("some_file.txt", cliArguments["filename"]);
	ASSERT_EQ("./", cliArguments["-s"]);
	ASSERT_EQ("./", cliArguments["--sourcedir"]);
	ASSERT_EQ("./", cliArguments["-d"]);
	ASSERT_EQ("./", cliArguments["--destdir"]);
	ASSERT_FALSE(cliArguments.isSet("-v"));
	ASSERT_FALSE(cliArguments.isSet("--verbose"));
	ASSERT_FALSE(cliArguments.isSet("-l"));
	ASSERT_FALSE(cliArguments.isSet("--followLinks"));

	argc = 4;
	char const * const argvSource[] = {"appName", "-s", "path/to/source/dir", "some_file.txt"};
	CLIArguments cliArguments2 = argumentParser.parseArguments(argc, argvSource);
	ASSERT_EQ("some_file.txt", cliArguments2["filename"]);
	ASSERT_EQ("path/to/source/dir", cliArguments2["-s"]);
	ASSERT_EQ("path/to/source/dir", cliArguments2["--sourcedir"]);
	ASSERT_EQ("./", cliArguments2["-d"]);
	ASSERT_EQ("./", cliArguments2["--destdir"]);
	ASSERT_FALSE(cliArguments2.isSet("-v"));
	ASSERT_FALSE(cliArguments2.isSet("--verbose"));
	ASSERT_FALSE(cliArguments2.isSet("-l"));
	ASSERT_FALSE(cliArguments2.isSet("--followLinks"));

	argc = 5;
	char const * const argvDestVerbose[] = {"appName", "--destdir", "path/to/dest/dir", "-v", "some_file.txt"};
	CLIArguments cliArguments3 = argumentParser.parseArguments(argc, argvDestVerbose);
	ASSERT_EQ("some_file.txt", cliArguments3["filename"]);
	ASSERT_EQ("./", cliArguments3["-s"]);
	ASSERT_EQ("./", cliArguments3["--sourcedir"]);
	ASSERT_EQ("path/to/dest/dir", cliArguments3["-d"]);
	ASSERT_EQ("path/to/dest/dir", cliArguments3["--destdir"]);
	ASSERT_TRUE(cliArguments3.isSet("-v"));
	ASSERT_TRUE(cliArguments3.isSet("--verbose"));
	ASSERT_FALSE(cliArguments3.isSet("-l"));
	ASSERT_FALSE(cliArguments3.isSet("--followLinks"));

	argc = 8;
	char const * const argvAll[] = {"appName", "-d", "path/to/dest/dir", "-v", "--sourcedir", "path/to/source/dir", "--followLinks", "some_file.txt"};
	CLIArguments cliArguments4 = argumentParser.parseArguments(argc, argvAll);
	ASSERT_EQ("some_file.txt", cliArguments4["filename"]);
	ASSERT_EQ("path/to/source/dir", cliArguments4["-s"]);
	ASSERT_EQ("path/to/source/dir", cliArguments4["--sourcedir"]);
	ASSERT_EQ("path/to/dest/dir", cliArguments4["-d"]);
	ASSERT_EQ("path/to/dest/dir", cliArguments4["--destdir"]);
	ASSERT_TRUE(cliArguments4.isSet("-v"));
	ASSERT_TRUE(cliArguments4.isSet("--verbose"));
	ASSERT_TRUE(cliArguments4.isSet("-l"));
	ASSERT_TRUE(cliArguments4.isSet("--followLinks"));
}
