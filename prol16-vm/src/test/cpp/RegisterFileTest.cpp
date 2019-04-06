/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "RegisterFile.h"

#include <stdexcept>

#include "gtest/gtest.h"

#include "RegisterError.h"

using namespace PROL16;

TEST(RegisterFileTest, testRegisterFileUsage) {
	RegisterFile registerFile;

	registerFile.write(5, 0xCAFE);
	ASSERT_EQ(0xCAFE, registerFile[5]);
	ASSERT_EQ(0xCAFE, registerFile.read(5));

	registerFile[6] = 0xABBA;
	ASSERT_EQ(0xABBA, registerFile[6]);
	ASSERT_EQ(0xABBA, registerFile.read(6));

	ASSERT_THROW(registerFile[16], util::RegisterError);
	ASSERT_THROW(registerFile.read(16), util::RegisterError);
	ASSERT_THROW(registerFile.write(16, 0xABBA), util::RegisterError);
}
