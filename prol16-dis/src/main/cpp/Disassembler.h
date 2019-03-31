/**
 * @author		creiterer
 * @date 		2019-03-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED
#define PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED

#include <istream>
#include <ostream>

#include "NonCopyable.h"

#include "Instruction.h"
#include "NumberUtils.h"

namespace PROL16 {

class Disassembler final : private NonCopyable {
public:
	using Immediate = util::Immediate;

	Disassembler(std::istream &sourceStream, std::ostream &destinationStream);
	~Disassembler() = default;

	void disassemble();

private:
	std::istream &sourceStream;
	std::ostream &destinationStream;

	Instruction readAndDecodeInstruction();
	Immediate readImmediate();
};

}

#endif /* PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED */
