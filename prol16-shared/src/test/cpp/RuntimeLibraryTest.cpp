/**
 * @author		creiterer
 * @date 		2019-10-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "RuntimeLibrary.h"

#include <gtest/gtest.h>

using namespace PROL16::rtlib;

TEST(RuntimeLibraryTest, testisRuntimeLibFunctionAddress) {
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FFF));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FFE));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FFD));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FFC));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FFB));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FFA));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF9));

	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x0));
	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x7FF8));
}

