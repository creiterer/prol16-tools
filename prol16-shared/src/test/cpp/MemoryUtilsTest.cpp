/**
 * @author		creiterer
 * @date 		2019-10-07
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "MemoryUtils.h"

#include <gtest/gtest.h>

using namespace PROL16::util::memory;

TEST(MemoryUtilsTest, testCalcStringSpaceInMemory) {
	ASSERT_EQ(1, calcStringSpaceInMemory(""));
	ASSERT_EQ(1, calcStringSpaceInMemory("a"));
	ASSERT_EQ(2, calcStringSpaceInMemory("ab"));
	ASSERT_EQ(2, calcStringSpaceInMemory("abc"));
	ASSERT_EQ(3, calcStringSpaceInMemory("abcd"));
	ASSERT_EQ(3, calcStringSpaceInMemory("abcde"));
}

