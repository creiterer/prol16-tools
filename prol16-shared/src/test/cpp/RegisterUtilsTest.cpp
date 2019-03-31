/**
 * @author		creiterer
 * @date 		2019-03-15
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Test utility functions of RegisterUtils
 */

#include "RegisterUtils.h"

#include "gtest/gtest.h"

#include "RegisterError.h"

using namespace PROL16::util;

TEST(RegisterUtilsTest, testIsRegisterValid) {
	ASSERT_TRUE(isRegisterValid(0));
	ASSERT_TRUE(isRegisterValid(RegisterCount-1));

	ASSERT_FALSE(isRegisterValid(RegisterCount));
	ASSERT_FALSE(isRegisterValid(20));
}

TEST(RegisterUtilsTest, testValidateRegister) {
	ASSERT_EQ(0, validateRegister(0));
	ASSERT_EQ(RegisterCount-1, validateRegister(RegisterCount-1));

	ASSERT_THROW(checkRegisterIsValid(RegisterCount), RegisterError);
	ASSERT_THROW(checkRegisterIsValid(33), RegisterError);
}

TEST(RegisterUtilsTest, testCheckRegisterIsValid) {
	ASSERT_NO_THROW(checkRegisterIsValid(0));
	ASSERT_NO_THROW(checkRegisterIsValid(RegisterCount-1));

	ASSERT_THROW(checkRegisterIsValid(RegisterCount), RegisterError);
	ASSERT_THROW(checkRegisterIsValid(33), RegisterError);
}

TEST(RegisterUtilsTest, testCheckRegistersAreValid) {
	/// @test with single register
	ASSERT_NO_THROW(checkRegistersAreValid(0));
	ASSERT_NO_THROW(checkRegistersAreValid(RegisterCount-1));

	ASSERT_THROW(checkRegistersAreValid(RegisterCount), RegisterError);
	ASSERT_THROW(checkRegistersAreValid(47), RegisterError);

	/// @test with multiple registers
	ASSERT_NO_THROW(checkRegistersAreValid(0, 0));
	ASSERT_NO_THROW(checkRegistersAreValid(0, RegisterCount-1));
	ASSERT_NO_THROW(checkRegistersAreValid(RegisterCount-1, 0));
	ASSERT_NO_THROW(checkRegistersAreValid(RegisterCount-1, RegisterCount-1));

	ASSERT_THROW(checkRegistersAreValid(RegisterCount, 0), RegisterError);
	ASSERT_THROW(checkRegistersAreValid(0, RegisterCount), RegisterError);
	ASSERT_THROW(checkRegistersAreValid(RegisterCount, RegisterCount), RegisterError);
}

TEST(RegisterUtilsTest, testIsSpecialRegister) {
	ASSERT_TRUE(isSpecialRegister("rsp"));
	ASSERT_TRUE(isSpecialRegister("RSP"));

	ASSERT_TRUE(isSpecialRegister("rfp"));
	ASSERT_TRUE(isSpecialRegister("RFP"));

	ASSERT_TRUE(isSpecialRegister("rra"));
	ASSERT_TRUE(isSpecialRegister("RRA"));

	ASSERT_FALSE(isSpecialRegister("rip"));
	ASSERT_FALSE(isSpecialRegister("r5"));
}

TEST(RegisterUtilsTest, testParseRegisterNumber) {
	ASSERT_EQ(0, parseRegisterNumber("r0"));
	ASSERT_EQ(0, parseRegisterNumber("R0"));

	ASSERT_EQ(15, parseRegisterNumber("r15"));
	ASSERT_EQ(15, parseRegisterNumber("R15"));

	ASSERT_EQ(16, parseRegisterNumber("r16"));
	ASSERT_EQ(16, parseRegisterNumber("R16"));

	ASSERT_EQ(0, parseRegisterNumber("rsp"));
	ASSERT_EQ(0, parseRegisterNumber("RSP"));

	ASSERT_EQ(1, parseRegisterNumber("rfp"));
	ASSERT_EQ(1, parseRegisterNumber("RFP"));

	ASSERT_EQ(2, parseRegisterNumber("rra"));
	ASSERT_EQ(2, parseRegisterNumber("RRA"));
}

TEST(RegisterUtilsTest, testParseRegisterNumberChecked) {
	ASSERT_EQ(0, parseRegisterNumberChecked("r0"));
	ASSERT_EQ(0, parseRegisterNumberChecked("R0"));

	ASSERT_EQ(15, parseRegisterNumberChecked("r15"));
	ASSERT_EQ(15, parseRegisterNumberChecked("R15"));

	ASSERT_EQ(0, parseRegisterNumberChecked("rsp"));
	ASSERT_EQ(0, parseRegisterNumberChecked("RSP"));

	ASSERT_THROW(parseRegisterNumberChecked("r16"), RegisterError);
	ASSERT_THROW(parseRegisterNumberChecked("R16"), RegisterError);

	ASSERT_THROW(parseRegisterNumberChecked("rip"), RegisterError);
	ASSERT_THROW(parseRegisterNumberChecked("RIP"), RegisterError);
}
