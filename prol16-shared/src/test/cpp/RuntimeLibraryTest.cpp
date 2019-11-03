/**
 * @author		creiterer
 * @date 		2019-10-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit tests for runtime library functions.
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
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF8));

	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x0));
	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x7FF7));
}

TEST(RuntimeLibraryTest, testGetRuntimeLibFunctionName) {
	ASSERT_EQ("_mul", getRuntimeLibFunctionName(MUL));
	ASSERT_EQ("_print", getRuntimeLibFunctionName(PRINT));
}
