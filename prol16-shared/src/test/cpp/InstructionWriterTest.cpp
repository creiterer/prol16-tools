/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit tests of the InstructionWriter class.
 */

#include "InstructionWriter.h"

#include <sstream>
#include <iostream>

#include "gtest/gtest.h"

#include "RegisterError.h"

using PROL16::util::InstructionWriter;
using PROL16::util::RegisterError;

#define TEST_INSTRUCTION_WRITE(statement, expectedValue) \
	do { \
		statement; \
		auto actualValue = instructionWriter.getLastInstruction(); \
		ASSERT_EQ(expectedValue, actualValue); \
		instructionWriter.clearCodeSegment(); \
	} while (false)

TEST(InstructionWriterTest, testAllInstructions) {
	InstructionWriter instructionWriter;
	instructionWriter.setCodeSegmentActive();

	TEST_INSTRUCTION_WRITE(instructionWriter.writeNop(), 0x0000);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeSleep(), 0x0400);

	instructionWriter.writeLoadi(14, 0xA5A5);
	InstructionWriter::Segment segment = instructionWriter.getCodeSegment();
	ASSERT_EQ(2, segment.size());
	ASSERT_EQ(0x9C0, segment[0]);
	ASSERT_EQ(0XA5A5, segment[1]);
	instructionWriter.clearCodeSegment();

	TEST_INSTRUCTION_WRITE(instructionWriter.writeLoad(14, 15), 0x0DCF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeStore(14, 15), 0x11CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeMove(14, 15), 0x31CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeJump(14), 0x21C0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeJumpc(14), 0x29C0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeJumpz(14), 0x2DC0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeAnd(14, 15), 0x41CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeOr(14, 15), 0x45CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeXor(14, 15), 0x49CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeNot(14), 0x4DC0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeAdd(14, 15), 0x51CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeAddc(14, 15), 0x55CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeSub(14, 15), 0x59CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeSubc(14, 15), 0x5DCF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeComp(14, 15), 0x61CF);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeInc(14), 0x69C0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeDec(14), 0x6DC0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeShl(14), 0x71C0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeShr(14), 0x75C0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeShlc(14), 0x79C0);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeShrc(14), 0x7DC0);
}

TEST(InstructionWriterTest, testWritingMultipleInstructions) {
	InstructionWriter instructionWriter;
	instructionWriter.setCodeSegmentActive();

	instructionWriter.writeLoadi(0, 0x8000);
	instructionWriter.writeLoad(1, 0);
	instructionWriter.writeInc(1);
	instructionWriter.writeSleep();

	InstructionWriter::Segment segment = instructionWriter.getCodeSegment();
	ASSERT_EQ(5, segment.size());
	ASSERT_EQ(0x800, segment[0]);
	ASSERT_EQ(0x8000, segment[1]);
	ASSERT_EQ(0x0C20, segment[2]);
	ASSERT_EQ(0x6820, segment[3]);
	ASSERT_EQ(0x0400, segment[4]);
}

TEST(InstructionWriterTest, testRegisterOutOfRange) {
	InstructionWriter instructionWriter;
	instructionWriter.setCodeSegmentActive();

	ASSERT_THROW(instructionWriter.writeLoadi(32, 0xAAAA), RegisterError);

	ASSERT_THROW(instructionWriter.writeLoad(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeLoad(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeLoad(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeStore(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeStore(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeStore(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeMove(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeMove(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeMove(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeJump(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeJumpc(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeJumpz(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeAnd(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeAnd(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeAnd(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeOr(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeOr(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeOr(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeXor(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeXor(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeXor(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeNot(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeAdd(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeAdd(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeAdd(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeAddc(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeAddc(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeAddc(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeSub(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeSub(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeSub(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeSubc(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeSubc(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeSubc(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeComp(32, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeComp(0, 32), RegisterError);
	ASSERT_THROW(instructionWriter.writeComp(32, 32), RegisterError);

	ASSERT_THROW(instructionWriter.writeInc(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeDec(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeShl(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeShr(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeShlc(32), RegisterError);

	ASSERT_THROW(instructionWriter.writeShrc(32), RegisterError);
}

TEST(InstructionWriterTest, testWritingDataWords) {
	InstructionWriter instructionWriter;
	instructionWriter.setDataSegmentActive();

	instructionWriter.writeImmediate(0xA5A5);
	instructionWriter.writeString("Hello World");
	InstructionWriter::Segment segment = instructionWriter.getDataSegment();

	ASSERT_EQ(7, segment.size());
	ASSERT_EQ(0xA5A5, segment[0]);
	ASSERT_EQ(('e' << 8) + 'H', segment[1]);
	ASSERT_EQ(('l' << 8) + 'l', segment[2]);
	ASSERT_EQ((' ' << 8) + 'o', segment[3]);
	ASSERT_EQ(('o' << 8) + 'W', segment[4]);
	ASSERT_EQ(('l' << 8) + 'r', segment[5]);
	ASSERT_EQ('d', segment[6]);
}
