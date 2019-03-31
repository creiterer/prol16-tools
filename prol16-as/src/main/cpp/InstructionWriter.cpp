/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "InstructionWriter.h"

#include "RegisterUtils.h"
#include "MnemonicUtils.h"

namespace PROL16 {

using namespace util;

void InstructionWriter::writeNop() {
	Instruction nop(NOP);
	instructionBuffer.push_back(nop);
}

void InstructionWriter::writeSleep() {
	Instruction sleep(SLEEP);
	instructionBuffer.push_back(sleep);
}

void InstructionWriter::writeLoadi(Register const ra, Immediate const immediate) {
	util::checkRegisterIsValid(ra);

	Instruction loadi(LOADI, ra);
	instructionBuffer.push_back(loadi);
	instructionBuffer.push_back(immediate);
}

void InstructionWriter::writeLoad(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction load(LOAD, ra, rb);
	instructionBuffer.push_back(load);
}

void InstructionWriter::writeStore(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction store(STORE, ra, rb);
	instructionBuffer.push_back(store);
}

void InstructionWriter::writeMove(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction move(MOVE, ra, rb);
	instructionBuffer.push_back(move);
}

void InstructionWriter::writeJump(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction jump(JUMP, ra);
	instructionBuffer.push_back(jump);
}

void InstructionWriter::writeJumpc(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction jumpc(JUMPC, ra);
	instructionBuffer.push_back(jumpc);
}

void InstructionWriter::writeJumpz(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction jumpz(JUMPZ, ra);
	instructionBuffer.push_back(jumpz);
}

void InstructionWriter::writeAnd(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction _and(AND, ra, rb);
	instructionBuffer.push_back(_and);
}

void InstructionWriter::writeOr(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction _or(OR, ra, rb);
	instructionBuffer.push_back(_or);
}

void InstructionWriter::writeXor(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction _xor(XOR, ra, rb);
	instructionBuffer.push_back(_xor);
}

void InstructionWriter::writeNot(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction _not(NOT, ra);
	instructionBuffer.push_back(_not);
}

void InstructionWriter::writeAdd(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction add(ADD, ra, rb);
	instructionBuffer.push_back(add);
}

void InstructionWriter::writeAddc(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction addc(ADDC, ra, rb);
	instructionBuffer.push_back(addc);
}

void InstructionWriter::writeSub(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction sub(SUB, ra, rb);
	instructionBuffer.push_back(sub);
}

void InstructionWriter::writeSubc(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction subc(SUBC, ra, rb);
	instructionBuffer.push_back(subc);
}

void InstructionWriter::writeComp(Register const ra, Register const rb) {
	util::checkRegistersAreValid(ra, rb);

	Instruction comp(COMP, ra, rb);
	instructionBuffer.push_back(comp);
}

void InstructionWriter::writeInc(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction inc(INC, ra);
	instructionBuffer.push_back(inc);
}

void InstructionWriter::writeDec(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction dec(DEC, ra);
	instructionBuffer.push_back(dec);
}

void InstructionWriter::writeShl(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction shl(SHL, ra);
	instructionBuffer.push_back(shl);
}

void InstructionWriter::writeShr(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction shr(SHR, ra);
	instructionBuffer.push_back(shr);
}

void InstructionWriter::writeShlc(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction shlc(SHLC, ra);
	instructionBuffer.push_back(shlc);
}

void InstructionWriter::writeShrc(Register const ra) {
	util::checkRegisterIsValid(ra);

	Instruction shrc(SHRC, ra);
	instructionBuffer.push_back(shrc);
}

void InstructionWriter::writeBufferToStream(std::ostream &stream) {
	stream.write(reinterpret_cast<char*>(instructionBuffer.data()), instructionBuffer.size()*(sizeof(InstructionBuffer::value_type)/sizeof(char)));
}

}
