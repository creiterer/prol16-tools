/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "InstructionWriter.h"

#include "FileUtils.h"
#include "MnemonicUtils.h"
#include "RegisterUtils.h"
#include "StringUtils.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

void InstructionWriter::writeNop() {
	instructionBuffer.push_back(Instruction(NOP));
}

void InstructionWriter::writeSleep() {
	instructionBuffer.push_back(Instruction(SLEEP));
}

void InstructionWriter::writeLoadi(Register const ra, Immediate const immediate) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(LOADI, ra));
	instructionBuffer.push_back(immediate);
}

void InstructionWriter::writeLoad(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(LOAD, ra, rb));
}

void InstructionWriter::writeStore(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(STORE, ra, rb));
}

void InstructionWriter::writeMove(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(MOVE, ra, rb));
}

void InstructionWriter::writeJump(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(JUMP, ra));
}

void InstructionWriter::writeJumpc(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(JUMPC, ra));
}

void InstructionWriter::writeJumpz(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(JUMPZ, ra));
}

void InstructionWriter::writeAnd(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(AND, ra, rb));
}

void InstructionWriter::writeOr(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(OR, ra, rb));
}

void InstructionWriter::writeXor(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(XOR, ra, rb));
}

void InstructionWriter::writeNot(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(NOT, ra));
}

void InstructionWriter::writeAdd(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(ADD, ra, rb));
}

void InstructionWriter::writeAddc(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(ADDC, ra, rb));
}

void InstructionWriter::writeSub(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(SUB, ra, rb));
}

void InstructionWriter::writeSubc(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(SUBC, ra, rb));
}

void InstructionWriter::writeComp(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	instructionBuffer.push_back(Instruction(COMP, ra, rb));
}

void InstructionWriter::writeInc(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(INC, ra));
}

void InstructionWriter::writeDec(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(DEC, ra));
}

void InstructionWriter::writeShl(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(SHL, ra));
}

void InstructionWriter::writeShr(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(SHR, ra));
}

void InstructionWriter::writeShlc(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(SHLC, ra));
}

void InstructionWriter::writeShrc(Register const ra) {
	util::checkRegisterIsValid(ra);

	instructionBuffer.push_back(Instruction(SHRC, ra));
}

void InstructionWriter::writeImmediate(Immediate const immediate) {
	instructionBuffer.push_back(immediate);
}

void InstructionWriter::writeString(String const &str) {
	std::vector<EncodedType> encodedString = ::util::encode<EncodedType>(str);
	instructionBuffer.insert(instructionBuffer.cend(), encodedString.cbegin(), encodedString.cend());
}

void InstructionWriter::writeBufferToStream(std::ostream &stream) const {
	::util::writeBufferToStream(stream, instructionBuffer);
}

} 	// namespace util
} 	// namespace PROL16
