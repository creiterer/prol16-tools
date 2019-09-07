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
		instructionWriter.clearInstructionBuffer(); \
	} while (false)

TEST(InstructionWriterTest, testAllInstructions) {
	InstructionWriter instructionWriter;

	TEST_INSTRUCTION_WRITE(instructionWriter.writeNop(), 0x0000);

	TEST_INSTRUCTION_WRITE(instructionWriter.writeSleep(), 0x0400);

	instructionWriter.writeLoadi(14, 0xA5A5);
	InstructionWriter::InstructionBuffer buffer = instructionWriter.getInstructionBuffer();
	ASSERT_EQ(2, buffer.size());
	ASSERT_EQ(0x9C0, buffer[0]);
	ASSERT_EQ(0XA5A5, buffer[1]);
	instructionWriter.clearInstructionBuffer();

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

	TEST_INSTRUCTION_WRITE(instructionWriter.writePrint(14), 0xF5C0);

	instructionWriter.writePrinti(0xA5A5);
	buffer = instructionWriter.getInstructionBuffer();
	ASSERT_EQ(2, buffer.size());
	ASSERT_EQ(0xF800, buffer[0]);
	ASSERT_EQ(0XA5A5, buffer[1]);
	instructionWriter.clearInstructionBuffer();

	TEST_INSTRUCTION_WRITE(instructionWriter.writePrintstr(14), 0xFDC0);
}

TEST(InstructionWriterTest, testWritingMultipleInstructions) {
	InstructionWriter instructionWriter;

	instructionWriter.writeLoadi(0, 0x8000);
	instructionWriter.writeLoad(1, 0);
	instructionWriter.writeInc(1);
	instructionWriter.writeSleep();

	InstructionWriter::InstructionBuffer instructionBuffer = instructionWriter.getInstructionBuffer();
	ASSERT_EQ(5, instructionBuffer.size());
	ASSERT_EQ(0x800, instructionBuffer[0]);
	ASSERT_EQ(0x8000, instructionBuffer[1]);
	ASSERT_EQ(0x0C20, instructionBuffer[2]);
	ASSERT_EQ(0x6820, instructionBuffer[3]);
	ASSERT_EQ(0x0400, instructionBuffer[4]);
}

TEST(InstructionWriterTest, testRegisterOutOfRange) {
	InstructionWriter instructionWriter;

	ASSERT_THROW(instructionWriter.writeLoadi(16, 0xAAAA), RegisterError);

	ASSERT_THROW(instructionWriter.writeLoad(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeLoad(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeLoad(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeStore(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeStore(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeStore(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeMove(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeMove(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeMove(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeJump(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeJumpc(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeJumpz(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeAnd(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeAnd(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeAnd(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeOr(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeOr(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeOr(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeXor(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeXor(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeXor(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeNot(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeAdd(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeAdd(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeAdd(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeAddc(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeAddc(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeAddc(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeSub(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeSub(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeSub(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeSubc(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeSubc(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeSubc(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeComp(16, 0), RegisterError);
	ASSERT_THROW(instructionWriter.writeComp(0, 16), RegisterError);
	ASSERT_THROW(instructionWriter.writeComp(16, 16), RegisterError);

	ASSERT_THROW(instructionWriter.writeInc(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeDec(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeShl(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeShr(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeShlc(16), RegisterError);

	ASSERT_THROW(instructionWriter.writeShrc(16), RegisterError);

	ASSERT_THROW(instructionWriter.writePrint(16), RegisterError);

	ASSERT_THROW(instructionWriter.writePrintstr(16), RegisterError);
}

TEST(InstructionWriterTest, testWritingDataWords) {
	InstructionWriter instructionWriter;

	TEST_INSTRUCTION_WRITE(instructionWriter.writeImmediate(0xA5A5), 0xA5A5);

	instructionWriter.writeString("Hello World");
	InstructionWriter::InstructionBuffer buffer = instructionWriter.getInstructionBuffer();
	ASSERT_EQ(6, buffer.size());
	ASSERT_EQ(('e' << 8) + 'H', buffer[0]);
	ASSERT_EQ(('l' << 8) + 'l', buffer[1]);
	ASSERT_EQ((' ' << 8) + 'o', buffer[2]);
	ASSERT_EQ(('o' << 8) + 'W', buffer[3]);
	ASSERT_EQ(('l' << 8) + 'r', buffer[4]);
	ASSERT_EQ('d', buffer[5]);
	instructionWriter.clearInstructionBuffer();
}
