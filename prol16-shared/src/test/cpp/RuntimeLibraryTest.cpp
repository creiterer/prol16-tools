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
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FF9));
	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x7FF8));

	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FEF));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FE6));
	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x7FE5));

	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FDF));
	ASSERT_TRUE(isRuntimeLibFunctionAddress(0x7FDD));
	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x7FDC));


	ASSERT_FALSE(isRuntimeLibFunctionAddress(0x0));
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
