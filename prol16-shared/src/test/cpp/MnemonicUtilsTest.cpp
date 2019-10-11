/**
 * @author		creiterer
 * @date 		2019-03-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "MnemonicUtils.h"

#include <stdexcept>

#include "gtest/gtest.h"

#include "OpcodeError.h"

using namespace PROL16::util;

TEST(MnemonicUtilsTest, testIsOpcodeValid) {
	ASSERT_TRUE(isOpcodeValid(0x0));
	ASSERT_TRUE(isOpcodeValid(0x1));
	ASSERT_TRUE(isOpcodeValid(0x1F));

	ASSERT_FALSE(isOpcodeValid(0x5));
	ASSERT_FALSE(isOpcodeValid(0x20));
}

TEST(MnemonicUtilsTest, testValidateOpcode) {
	ASSERT_EQ(0x0, validateOpcode(0x0));
	ASSERT_EQ(0x1, validateOpcode(0x1));
	ASSERT_EQ(0x1F, validateOpcode(0x1F));

	ASSERT_THROW(validateOpcode(0x5), OpcodeError);
	ASSERT_THROW(validateOpcode(0x20), OpcodeError);
}

TEST(MnemonicUtilsTest, testGetMnemonicStringOfOpcode) {
	ASSERT_EQ("nop", getMnemonicStringOfOpcode(0x0));
	ASSERT_EQ("sleep", getMnemonicStringOfOpcode(0x1));
	ASSERT_EQ("loadi", getMnemonicStringOfOpcode(0x2));
	ASSERT_EQ("load", getMnemonicStringOfOpcode(0x3));
	ASSERT_EQ("store", getMnemonicStringOfOpcode(0x4));
	ASSERT_EQ("move", getMnemonicStringOfOpcode(0xC));
	ASSERT_EQ("jump", getMnemonicStringOfOpcode(0x8));
	ASSERT_EQ("jumpc", getMnemonicStringOfOpcode(0xA));
	ASSERT_EQ("jumpz", getMnemonicStringOfOpcode(0xB));
	ASSERT_EQ("and", getMnemonicStringOfOpcode(0x10));
	ASSERT_EQ("or", getMnemonicStringOfOpcode(0x11));
	ASSERT_EQ("xor", getMnemonicStringOfOpcode(0x12));
	ASSERT_EQ("not", getMnemonicStringOfOpcode(0x13));
	ASSERT_EQ("add", getMnemonicStringOfOpcode(0x14));
	ASSERT_EQ("addc", getMnemonicStringOfOpcode(0x15));
	ASSERT_EQ("sub", getMnemonicStringOfOpcode(0x16));
	ASSERT_EQ("subc", getMnemonicStringOfOpcode(0x17));
	ASSERT_EQ("comp", getMnemonicStringOfOpcode(0x18));
	ASSERT_EQ("inc", getMnemonicStringOfOpcode(0x1A));
	ASSERT_EQ("dec", getMnemonicStringOfOpcode(0x1B));
	ASSERT_EQ("shl", getMnemonicStringOfOpcode(0x1C));
	ASSERT_EQ("shr", getMnemonicStringOfOpcode(0x1D));
	ASSERT_EQ("shlc", getMnemonicStringOfOpcode(0x1E));
	ASSERT_EQ("shrc", getMnemonicStringOfOpcode(0x1F));

	ASSERT_THROW(getMnemonicStringOfOpcode(0x5), std::out_of_range);
}

TEST(MnemonicUtilsTest, testGetMnemonicAsString) {
	ASSERT_EQ("nop", getMnemonicAsString(NOP));
	ASSERT_EQ("sleep", getMnemonicAsString(SLEEP));
	ASSERT_EQ("loadi", getMnemonicAsString(LOADI));
	ASSERT_EQ("load", getMnemonicAsString(LOAD));
	ASSERT_EQ("store", getMnemonicAsString(STORE));
	ASSERT_EQ("move", getMnemonicAsString(MOVE));
	ASSERT_EQ("jump", getMnemonicAsString(JUMP));
	ASSERT_EQ("jumpc", getMnemonicAsString(JUMPC));
	ASSERT_EQ("jumpz", getMnemonicAsString(JUMPZ));
	ASSERT_EQ("and", getMnemonicAsString(AND));
	ASSERT_EQ("or", getMnemonicAsString(OR));
	ASSERT_EQ("xor", getMnemonicAsString(XOR));
	ASSERT_EQ("not", getMnemonicAsString(NOT));
	ASSERT_EQ("add", getMnemonicAsString(ADD));
	ASSERT_EQ("addc", getMnemonicAsString(ADDC));
	ASSERT_EQ("sub", getMnemonicAsString(SUB));
	ASSERT_EQ("subc", getMnemonicAsString(SUBC));
	ASSERT_EQ("comp", getMnemonicAsString(COMP));
	ASSERT_EQ("inc", getMnemonicAsString(INC));
	ASSERT_EQ("dec", getMnemonicAsString(DEC));
	ASSERT_EQ("shl", getMnemonicAsString(SHL));
	ASSERT_EQ("shr", getMnemonicAsString(SHR));
	ASSERT_EQ("shlc", getMnemonicAsString(SHLC));
	ASSERT_EQ("shrc", getMnemonicAsString(SHRC));

	ASSERT_THROW(getMnemonicAsString(static_cast<Mnemonic>(0x5)), std::out_of_range);
}

TEST(MnemonicUtilsTest, testNumberOfRegisterOperands) {
	ASSERT_EQ(0, numberOfRegisterOperands(NOP));
	ASSERT_EQ(0, numberOfRegisterOperands(SLEEP));
	ASSERT_EQ(1, numberOfRegisterOperands(LOADI));
	ASSERT_EQ(2, numberOfRegisterOperands(LOAD));
	ASSERT_EQ(2, numberOfRegisterOperands(STORE));
	ASSERT_EQ(2, numberOfRegisterOperands(MOVE));
	ASSERT_EQ(1, numberOfRegisterOperands(JUMP));
	ASSERT_EQ(1, numberOfRegisterOperands(JUMPC));
	ASSERT_EQ(1, numberOfRegisterOperands(JUMPZ));
	ASSERT_EQ(2, numberOfRegisterOperands(AND));
	ASSERT_EQ(2, numberOfRegisterOperands(OR));
	ASSERT_EQ(2, numberOfRegisterOperands(XOR));
	ASSERT_EQ(1, numberOfRegisterOperands(NOT));
	ASSERT_EQ(2, numberOfRegisterOperands(ADD));
	ASSERT_EQ(2, numberOfRegisterOperands(ADDC));
	ASSERT_EQ(2, numberOfRegisterOperands(SUB));
	ASSERT_EQ(2, numberOfRegisterOperands(SUBC));
	ASSERT_EQ(2, numberOfRegisterOperands(COMP));
	ASSERT_EQ(1, numberOfRegisterOperands(INC));
	ASSERT_EQ(1, numberOfRegisterOperands(DEC));
	ASSERT_EQ(1, numberOfRegisterOperands(SHL));
	ASSERT_EQ(1, numberOfRegisterOperands(SHR));
	ASSERT_EQ(1, numberOfRegisterOperands(SHLC));
	ASSERT_EQ(1, numberOfRegisterOperands(SHRC));

	ASSERT_EQ(0, numberOfRegisterOperands(0x0));
	ASSERT_EQ(1, numberOfRegisterOperands(0x2));
	ASSERT_EQ(2, numberOfRegisterOperands(0x3));

	ASSERT_THROW(numberOfRegisterOperands(0x5), std::invalid_argument);
}

TEST(MnemonicUtilsTest, testIsAnyJump) {
	ASSERT_TRUE(isAnyJump(JUMP));
	ASSERT_TRUE(isAnyJump(JUMPC));
	ASSERT_TRUE(isAnyJump(JUMPZ));

	ASSERT_FALSE(isAnyJump(NOP));
	ASSERT_FALSE(isAnyJump(LOADI));
}
