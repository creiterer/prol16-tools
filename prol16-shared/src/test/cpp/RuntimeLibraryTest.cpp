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
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF7));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF6));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF5));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF4));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF3));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF2));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF1));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF0));

	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x0));
	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x7FEF));
}

TEST(RuntimeLibraryTest, testGetRuntimeLibFunctionName) {
	ASSERT_EQ("__prol16_mul_i16", getRuntimeLibFunctionName(MUL_I16));
	ASSERT_EQ("__prol16_print_uint16", getRuntimeLibFunctionName(PRINT_UINT16));
}

TEST(RuntimeLibraryTest, testIsDiv32) {
	ASSERT_TRUE(isDiv32(SDIV_I32));
	ASSERT_TRUE(isDiv32(UDIV_I32));
	ASSERT_FALSE(isDiv32(SDIV_I16));
	ASSERT_FALSE(isDiv32(UDIV_I16));
}

TEST(RuntimeLibraryTest, testIsRem32) {
	ASSERT_TRUE(isRem32(SREM_I32));
	ASSERT_TRUE(isRem32(UREM_I32));
	ASSERT_FALSE(isRem32(SREM_I16));
	ASSERT_FALSE(isRem32(UREM_I16));
}
