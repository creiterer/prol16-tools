/**
 * @author		creiterer
 * @date 		2019-03-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED
#define PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED

#include "Instruction.h"
#include "NonCopyable.h"
#include "NumberUtils.h"

#include <istream>
#include <ostream>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class Disassembler final : private ::util::NonCopyable {
public:
	using Immediate = util::Immediate;

	Disassembler(std::istream &sourceStream, std::ostream &destinationStream);

	void disassemble();

private:
	std::istream &sourceStream;
	std::ostream &destinationStream;

	Instruction readAndDecodeInstruction();
	Immediate readImmediate();
};

}	// namespace PROL16

#endif /* PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED */
