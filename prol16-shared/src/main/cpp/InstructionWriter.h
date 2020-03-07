/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utility class for writing instructions to an instruction buffer.
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_INSTRUCTIONWRITER_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_INSTRUCTIONWRITER_H_INCLUDED

#include "Instruction.h"
#include "NonCopyable.h"
#include "NumberUtils.h"
#include "RegisterUtils.h"

#include <ostream>
#include <string>
#include <vector>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class InstructionWriter final : private ::util::NonCopyable {
public:
	using Register = util::Register;
	using Immediate = util::Immediate;
	using String = std::string;
	using EncodedType = Instruction::EncodedType;
	using Segment = std::vector<EncodedType>;

	InstructionWriter() = default;

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

	void writeImmediate(Immediate const immediate);

	void writeString(String const &str);

	inline Segment getCodeSegment() const noexcept { return codeSegment; }
	inline void clearCodeSegment() { codeSegment.clear(); }
	inline Instruction::EncodedType getLastInstruction() const { return codeSegment.back(); }

	inline Segment getDataSegment() const noexcept { return dataSegment; }

	inline void setCodeSegmentActive() noexcept { activeSegment = &codeSegment; }
	inline void setDataSegmentActive() noexcept { activeSegment = &dataSegment; }

private:
	Segment codeSegment;
	Segment dataSegment;
	Segment *activeSegment{nullptr};
};

} 	// namespace util
} 	// namespace PROL16

#endif /* PROL16_AS_SRC_MAIN_CPP_INSTRUCTIONWRITER_H_INCLUDED */
