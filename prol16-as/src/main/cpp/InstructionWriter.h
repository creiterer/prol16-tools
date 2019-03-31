/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_INSTRUCTIONWRITER_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_INSTRUCTIONWRITER_H_INCLUDED

#include <ostream>
#include <vector>

#include "NonCopyable.h"
#include "Instruction.h"
#include "RegisterUtils.h"
#include "NumberUtils.h"

namespace PROL16 {

class InstructionWriter final : private NonCopyable {
public:
	using Register = util::Register;
	using Immediate = util::Immediate;
	using InstructionBuffer = std::vector<Instruction::EncodedType>;

	InstructionWriter() = default;
	~InstructionWriter() = default;

	void writeNop();

	void writeSleep();

	void writeLoadi(Register const ra, Immediate const immediate);

	void writeLoad(Register const ra, Register const rb);

	void writeStore(Register const ra, Register const rb);

	void writeMove(Register const ra, Register const rb);

	void writeJump(Register const ra);

	void writeJumpc(Register const ra);

	void writeJumpz(Register const ra);

	void writeAnd(Register const ra, Register const rb);

	void writeOr(Register const ra, Register const rb);

	void writeXor(Register const ra, Register const rb);

	void writeNot(Register const ra);

	void writeAdd(Register const ra, Register const rb);

	void writeAddc(Register const ra, Register const rb);

	void writeSub(Register const ra, Register const rb);

	void writeSubc(Register const ra, Register const rb);

	void writeComp(Register const ra, Register const rb);

	void writeInc(Register const ra);

	void writeDec(Register const ra);

	void writeShl(Register const ra);

	void writeShr(Register const ra);

	void writeShlc(Register const ra);

	void writeShrc(Register const ra);

	void writeBufferToStream(std::ostream &stream);

	inline InstructionBuffer getInstructionBuffer() const { return instructionBuffer; }
	inline void clearInstructionBuffer() { instructionBuffer.clear(); }
	inline Instruction::EncodedType getLastInstruction() const { return instructionBuffer.back(); }

private:
	InstructionBuffer instructionBuffer;
};

}

#endif /* PROL16_AS_SRC_MAIN_CPP_INSTRUCTIONWRITER_H_INCLUDED */
