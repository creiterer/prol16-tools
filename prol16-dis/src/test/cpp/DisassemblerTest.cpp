/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Disassembler.h"

#include "IncompleteInstructionError.h"
#include "InstructionDecodeError.h"
#include "Prol16ExeParseError.h"
#include "ScopedFileStream.h"

#include "gtest/gtest.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

using ::util::ScopedFileStream;
using PROL16::util::Prol16ExeParseError;

TEST(DisassemblerTest, testSingleInstruction) {
	ScopedFileStream<std::ifstream> inputStream("resources/single_instruction.p16", std::ifstream::binary);
	std::ostringstream outputStream;

	PROL16::Disassembler disassembler(inputStream, outputStream);
	disassembler.disassemble();

	std::ostringstream expectedOutput;
	expectedOutput << "entry point address: 0000\n";
	expectedOutput << "0000:\tsleep\n";

	ASSERT_EQ(expectedOutput.str(), outputStream.str());
}

TEST(DisassemblerTest, testMultipleInstructions) {
	ScopedFileStream<std::ifstream> inputStream("resources/multiple_instructions.p16", std::ifstream::binary);
	std::ostringstream outputStream;

	PROL16::Disassembler disassembler(inputStream, outputStream);
	disassembler.disassemble();

	std::ostringstream expectedOutput;
	expectedOutput << "entry point address: 0000\n";
	expectedOutput << "0000:\t" << "nop" << std::endl;
	expectedOutput << "0001:\t" << "sleep" << std::endl;
	expectedOutput << "0002:\t" << "loadi rpc, 8080h" << std::endl;
	expectedOutput << "0004:\t" << "load rra, rpc" << std::endl;
	expectedOutput << "0005:\t" << "store rra, rpc" << std::endl;
	expectedOutput << "0006:\t" << "move rra, rpc" << std::endl;
	expectedOutput << "0007:\t" << "jump rpc" << std::endl;
	expectedOutput << "0008:\t" << "jumpc rpc" << std::endl;
	expectedOutput << "0009:\t" << "jumpz rpc" << std::endl;
	expectedOutput << "000A:\t" << "and rra, rpc" << std::endl;
	expectedOutput << "000B:\t" << "or rra, rpc" << std::endl;
	expectedOutput << "000C:\t" << "xor rra, rpc" << std::endl;
	expectedOutput << "000D:\t" << "not rra" << std::endl;
	expectedOutput << "000E:\t" << "add rra, rpc" << std::endl;
	expectedOutput << "000F:\t" << "addc rra, rpc" << std::endl;
	expectedOutput << "0010:\t" << "sub rra, rpc" << std::endl;
	expectedOutput << "0011:\t" << "subc rra, rpc" << std::endl;
	expectedOutput << "0012:\t" << "comp rra, rpc" << std::endl;
	expectedOutput << "0013:\t" << "inc rra" << std::endl;
	expectedOutput << "0014:\t" << "dec rra" << std::endl;
	expectedOutput << "0015:\t" << "shl rra" << std::endl;
	expectedOutput << "0016:\t" << "shr rra" << std::endl;
	expectedOutput << "0017:\t" << "shlc rra" << std::endl;
	expectedOutput << "0018:\t" << "shrc rra" << std::endl;
	expectedOutput << "0019:\t" << "load r15, r14" << std::endl;

	ASSERT_EQ(expectedOutput.str(), outputStream.str());
}

TEST(DisassemblerTest, testInvalidInstruction) {
	ScopedFileStream<std::ifstream> inputStream("resources/invalid_instruction.p16", std::ifstream::binary);
	std::ostringstream outputStream;

	PROL16::Disassembler disassembler(inputStream, outputStream);
	ASSERT_THROW(disassembler.disassemble(), PROL16::util::InstructionDecodeError);
}

TEST(DisassemblerTest, testIncompleteInstruction) {
	ScopedFileStream<std::ifstream> inputStream("resources/incomplete_instruction.p16", std::ifstream::binary);
	std::ostringstream outputStream;

	ASSERT_THROW(PROL16::Disassembler disassembler(inputStream, outputStream), std::runtime_error);
}

TEST(DisassemblerTest, testMissingImmediate) {
	ScopedFileStream<std::ifstream> inputStream("resources/missing_immediate.p16", std::ifstream::binary);
	std::ostringstream outputStream;

	PROL16::Disassembler disassembler(inputStream, outputStream);
	ASSERT_THROW(disassembler.disassemble(), PROL16::util::IncompleteInstructionError);
}


TEST(DisassemblerTest, testMissingMagicNumber) {
	ScopedFileStream<std::ifstream> inputStream("resources/empty.p16", std::ifstream::binary);
	std::ostringstream outputStream;

	ASSERT_THROW(PROL16::Disassembler disassembler(inputStream, outputStream), Prol16ExeParseError);
}

TEST(DisassemblerTest, testMissingEntryPoint) {
	ScopedFileStream<std::ifstream> inputStream("resources/missing_entry_point.p16", std::ifstream::binary);
	std::ostringstream outputStream;

	ASSERT_THROW(PROL16::Disassembler disassembler(inputStream, outputStream), Prol16ExeParseError);
}
