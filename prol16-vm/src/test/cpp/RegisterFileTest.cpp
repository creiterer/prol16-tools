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
	RegisterFile registerFile(0xFFFF);

	ASSERT_EQ(0xFFFF, registerFile.readStackPointer());
	ASSERT_EQ(0xFFFF, registerFile.readFramePointer());

	registerFile.write(5, 0xCAFE);
	ASSERT_EQ(0xCAFE, registerFile[5]);
	ASSERT_EQ(0xCAFE, registerFile.read(5));

	registerFile[6] = 0xABBA;
	ASSERT_EQ(0xABBA, registerFile[6]);
	ASSERT_EQ(0xABBA, registerFile.read(6));

	registerFile.writeProgramCounter(0xBABE);
	ASSERT_EQ(0xBABE, registerFile[0]);
	ASSERT_EQ(0xBABE, registerFile.readProgramCounter());

	registerFile.writeStackPointer(0xFACE);
	ASSERT_EQ(0xFACE, registerFile[2]);
	ASSERT_EQ(0xFACE, registerFile.readStackPointer());

	registerFile.writeFramePointer(0xC0DE);
	ASSERT_EQ(0xC0DE, registerFile[3]);
	ASSERT_EQ(0xC0DE, registerFile.readFramePointer());

	ASSERT_THROW(registerFile[16], util::RegisterError);
	ASSERT_THROW(registerFile.read(16), util::RegisterError);
	ASSERT_THROW(registerFile.write(16, 0xABBA), util::RegisterError);
}
