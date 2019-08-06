/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Instruction.h"

#include "gtest/gtest.h"

#include "MnemonicUtils.h"
#include "InstructionDecodeError.h"

using namespace PROL16;
using PROL16::util::InstructionDecodeError;

TEST(InstructionTest, testInstructionEncoding) {
	Instruction nop(0x0);
	/*
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 00 | 00 000 | 0 0000 |
	 *  | 0000 | 0000 | 0000 | 0000 |
	 *  |   0  |   0  |   0  |   0  |
	 */
	ASSERT_EQ(0x0000, nop);
	ASSERT_EQ(0x0000, nop.encode());

	Instruction sleep(0x1);
	/*
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 01 | 00 000 | 0 0000 |
	 *  | 0000 | 0100 | 0000 | 0000 |
	 *  |   0  |   4  |   0  |   0  |
	 */
	ASSERT_EQ(0x0400, sleep);
	ASSERT_EQ(0x0400, sleep.encode());

	Instruction loadi(0x2, 0);
	/*
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 10 | 00 000 | 0 0000 |
	 *  | 0000 | 1000 | 0000 | 0000 |
	 *  |   0  |   8  |   0  |   0  |
	 */
	ASSERT_EQ(0x0800, loadi);
	ASSERT_EQ(0x0800, loadi.encode());

	Instruction load(0x3, 14, 15);
	/*
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 11 | 01 110 | 0 1111 |
	 *  | 0000 | 1101 | 1100 | 1111 |
	 *  |   0  |   D  |   C  |   F  |
	 */
	ASSERT_EQ(0X0DCF, load);
	ASSERT_EQ(0X0DCF, load.encode());
}

TEST(InstructionTest, testInstructionDecoding) {
	/*
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 00 | 00 000 | 0 0000 |
	 *  | 0000 | 0000 | 0000 | 0000 |
	 *  |   0  |   0  |   0  |   0  |
	 */
	Instruction nop = Instruction::decode(0x0000);
	ASSERT_EQ(0, nop.getRb());
	ASSERT_EQ(0, nop.getRa());
	ASSERT_EQ(0x0, nop.getOpcode());

	/*
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 01 | 00 000 | 0 0000 |
	 *  | 0000 | 0100 | 0000 | 0000 |
	 *  |   0  |   4  |   0  |   0  |
	 */
	Instruction sleep = Instruction::decode(0x0400);
	ASSERT_EQ(0, sleep.getRb());
	ASSERT_EQ(0, sleep.getRa());
	ASSERT_EQ(0x1, sleep.getOpcode());

	/*
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 10 | 00 000 | 0 0000 |
	 *  | 0000 | 1000 | 0000 | 0000 |
	 *  |   0  |   8  |   0  |   0  |
	 */
	Instruction loadi = Instruction::decode(0x0800);
	ASSERT_EQ(0, loadi.getRb());
	ASSERT_EQ(0, loadi.getRa());
	ASSERT_EQ(0x2, loadi.getOpcode());

	/*
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 11 | 01 110 | 0 1111 |
	 *  | 0000 | 1101 | 1100 | 1111 |
	 *  |   0  |   D  |   C  |   F  |
	 */
	Instruction load = Instruction::decode(0X0DCF);
	ASSERT_EQ(15, load.getRb());
	ASSERT_EQ(14, load.getRa());
	ASSERT_EQ(0x3, load.getOpcode());

	/** @test invalid rb
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 11 | 01 110 | 1 0000 |
	 *  | 0000 | 1101 | 1101 | 0000 |
	 *  |   0  |   D  |   D  |   0  |
	 */
	ASSERT_THROW(Instruction::decode(0x0DD0), InstructionDecodeError);


	/** @test invalid ra
	 *  | opcode  |   ra   |   rb   |
	 *  | 0000 11 | 10 000 | 0 1111 |
	 *  | 0000 | 1110 | 0000 | 1111 |
	 *  |   0  |   E  |   0  |   F  |
	 */
	ASSERT_THROW(Instruction::decode(0x0E0F), InstructionDecodeError);

	/** @test invalid opcode
	 *  | opcode  |   ra   |   rb   |
	 *  | 1000 11 | 01 110 | 0 1111 |
	 *  | 1000 | 1101 | 1100 | 1111 |
	 *  |   8  |   D  |   C  |   F  |
	 */
	ASSERT_THROW(Instruction::decode(0x8DCF), InstructionDecodeError);
}

TEST(InstructionTest, testAsString) {
	using namespace PROL16::util;

	Instruction nop(NOP);
	ASSERT_EQ("nop", nop.asString());

	Instruction sleep(SLEEP);
	ASSERT_EQ("sleep", sleep.asString());

	Instruction loadi(LOADI, 14);
	ASSERT_EQ("loadi r14", loadi.asString());

	Instruction load(LOAD, 14, 15);
	ASSERT_EQ("load r14, r15", load.asString());

	Instruction store(STORE, 14, 15);
	ASSERT_EQ("store r14, r15", store.asString());

	Instruction move(MOVE, 14, 15);
	ASSERT_EQ("move r14, r15", move.asString());

	Instruction jump(JUMP, 14);
	ASSERT_EQ("jump r14", jump.asString());

	Instruction jumpc(JUMPC, 14);
	ASSERT_EQ("jumpc r14", jumpc.asString());

	Instruction jumpz(JUMPZ, 14);
	ASSERT_EQ("jumpz r14", jumpz.asString());

	Instruction _and(AND, 14, 15);
	ASSERT_EQ("and r14, r15", _and.asString());

	Instruction _or(OR, 14, 15);
	ASSERT_EQ("or r14, r15", _or.asString());

	Instruction _xor(XOR, 14, 15);
	ASSERT_EQ("xor r14, r15", _xor.asString());

	Instruction _not(NOT, 14);
	ASSERT_EQ("not r14", _not.asString());

	Instruction add(ADD, 14, 15);
	ASSERT_EQ("add r14, r15", add.asString());

	Instruction addc(ADDC, 14, 15);
	ASSERT_EQ("addc r14, r15", addc.asString());

	Instruction sub(SUB, 14, 15);
	ASSERT_EQ("sub r14, r15", sub.asString());

	Instruction subc(SUBC, 14, 15);
	ASSERT_EQ("subc r14, r15", subc.asString());

	Instruction comp(COMP, 14, 15);
	ASSERT_EQ("comp r14, r15", comp.asString());

	Instruction inc(INC, 14);
	ASSERT_EQ("inc r14", inc.asString());

	Instruction dec(DEC, 14);
	ASSERT_EQ("dec r14", dec.asString());

	Instruction shl(SHL, 14);
	ASSERT_EQ("shl r14", shl.asString());

	Instruction shr(SHR, 14);
	ASSERT_EQ("shr r14", shr.asString());

	Instruction shlc(SHLC, 14);
	ASSERT_EQ("shlc r14", shlc.asString());

	Instruction shrc(SHRC, 14);
	ASSERT_EQ("shrc r14", shrc.asString());
}

TEST(InstructionTest, testIs) {
	using namespace PROL16::util;

	Instruction nop(0x0);
	ASSERT_TRUE(nop.is(NOP));
	ASSERT_FALSE(nop.is(SLEEP));

	Instruction loadi(0x2, 0);
	ASSERT_TRUE(loadi.is(LOADI));
	ASSERT_FALSE(loadi.is(LOAD));

	Instruction load(0x3, 14, 15);
	ASSERT_TRUE(load.is(LOAD));
	ASSERT_FALSE(load.is(STORE));
}
