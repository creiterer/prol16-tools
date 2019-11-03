/**
 * @author		creiterer
 * @date 		2019-10-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit test of the CLIArgumentNames class.
 */

#include "CLIArgumentNames.h"

#include <gtest/gtest.h>

using namespace util::cli;

TEST(CLIArgumentNamesTest, testOperatorEqualTo) {
	ASSERT_TRUE(flags::HELP == "-h");
	ASSERT_TRUE(flags::HELP == "--help");
	ASSERT_FALSE(flags::HELP == "-i");

	ASSERT_TRUE("-h" == flags::HELP);
	ASSERT_TRUE("--help" == flags::HELP);
	ASSERT_FALSE("-i" == flags::HELP);
}

