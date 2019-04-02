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

TEST(RegisterUtilsTest, testGetCanonicalRegisterName) {
	ASSERT_EQ("r0", getCanonicalRegisterName("r0"));
	ASSERT_EQ("r0", getCanonicalRegisterName("R0"));
	ASSERT_EQ("r0", getCanonicalRegisterName("0"));
	ASSERT_EQ("r15", getCanonicalRegisterName("r15"));
	ASSERT_EQ("r15", getCanonicalRegisterName("R15"));
	ASSERT_EQ("r15", getCanonicalRegisterName("15"));

	ASSERT_EQ("rsp", getCanonicalRegisterName("rsp"));
	ASSERT_EQ("rsp", getCanonicalRegisterName("RSP"));
	ASSERT_EQ("rsp", getCanonicalRegisterName("sp"));
	ASSERT_EQ("rsp", getCanonicalRegisterName("SP"));

	ASSERT_EQ("rra", getCanonicalRegisterName("rra"));
	ASSERT_EQ("rra", getCanonicalRegisterName("RRA"));
	ASSERT_EQ("rra", getCanonicalRegisterName("ra"));
	ASSERT_EQ("rra", getCanonicalRegisterName("RA"));
}

TEST(RegisterUtilsTest, testIsSpecialRegister) {
	ASSERT_TRUE(isSpecialRegister("rsp"));
	ASSERT_TRUE(isSpecialRegister("RSP"));

	ASSERT_TRUE(isSpecialRegister("rfp"));
	ASSERT_TRUE(isSpecialRegister("RFP"));

	ASSERT_TRUE(isSpecialRegister("rra"));
	ASSERT_TRUE(isSpecialRegister("RRA"));

	ASSERT_TRUE(isSpecialRegister("sp"));
	ASSERT_TRUE(isSpecialRegister("SP"));

	ASSERT_TRUE(isSpecialRegister("fp"));
	ASSERT_TRUE(isSpecialRegister("FP"));

	ASSERT_TRUE(isSpecialRegister("ra"));
	ASSERT_TRUE(isSpecialRegister("RA"));

	ASSERT_FALSE(isSpecialRegister("rip"));
	ASSERT_FALSE(isSpecialRegister("ip"));

	ASSERT_FALSE(isSpecialRegister("r5"));
	ASSERT_FALSE(isSpecialRegister("r15"));
}

TEST(RegisterUtilsTest, testIsReturnAddressRegister) {
	ASSERT_TRUE(isReturnAddressRegister("ra"));
	ASSERT_TRUE(isReturnAddressRegister("RA"));

	ASSERT_TRUE(isReturnAddressRegister("rra"));
	ASSERT_TRUE(isReturnAddressRegister("RRA"));

	ASSERT_FALSE(isReturnAddressRegister("sp"));
	ASSERT_FALSE(isReturnAddressRegister("rsp"));

	ASSERT_FALSE(isReturnAddressRegister("0"));
	ASSERT_FALSE(isReturnAddressRegister("r0"));

	ASSERT_FALSE(isReturnAddressRegister("15"));
	ASSERT_FALSE(isReturnAddressRegister("r15"));
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

	ASSERT_EQ(0, parseRegisterNumber("0"));
	ASSERT_EQ(15, parseRegisterNumber("15"));
	ASSERT_EQ(16, parseRegisterNumber("16"));

	ASSERT_EQ(0, parseRegisterNumber("sp"));
	ASSERT_EQ(1, parseRegisterNumber("fp"));
	ASSERT_EQ(2, parseRegisterNumber("ra"));

	ASSERT_THROW(parseRegisterNumber(""), std::invalid_argument);
}

TEST(RegisterUtilsTest, testParseRegisterNumberChecked) {
	ASSERT_EQ(0, parseRegisterNumberChecked("r0"));
	ASSERT_EQ(0, parseRegisterNumberChecked("R0"));

	ASSERT_EQ(15, parseRegisterNumberChecked("r15"));
	ASSERT_EQ(15, parseRegisterNumberChecked("R15"));

	ASSERT_EQ(0, parseRegisterNumberChecked("rsp"));
	ASSERT_EQ(0, parseRegisterNumberChecked("RSP"));

	ASSERT_EQ(0, parseRegisterNumberChecked("0"));
	ASSERT_EQ(15, parseRegisterNumberChecked("15"));

	ASSERT_EQ(2, parseRegisterNumberChecked("ra"));

	ASSERT_THROW(parseRegisterNumberChecked("r16"), RegisterError);
	ASSERT_THROW(parseRegisterNumberChecked("R16"), RegisterError);
	ASSERT_THROW(parseRegisterNumberChecked("16"), RegisterError);

	ASSERT_THROW(parseRegisterNumberChecked("rip"), RegisterError);
	ASSERT_THROW(parseRegisterNumberChecked("RIP"), RegisterError);
	ASSERT_THROW(parseRegisterNumberChecked("ip"), RegisterError);

	ASSERT_THROW(parseRegisterNumberChecked(""), RegisterError);
}
