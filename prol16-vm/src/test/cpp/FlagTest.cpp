/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Flag.h"
#include "FlagError.h"

#include "gtest/gtest.h"

using namespace PROL16;
using PROL16::util::FlagError;

TEST(FlagTest, testFlagUsage) {
	Flag flag("test flag");
	ASSERT_THROW(flag.isSet(), FlagError);

	flag.reset();
	ASSERT_FALSE(flag.isSet());

	flag.set();
	ASSERT_TRUE(flag.isSet());

	flag.set(false);
	ASSERT_FALSE(flag.isSet());
}

