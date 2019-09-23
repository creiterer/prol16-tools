/**
 * @author		creiterer
 * @date 		2019-03-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED
#define PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED

#include "Instruction.h"
#include "MemoryUtils.h"
#include "NonCopyable.h"
#include "NumberUtils.h"
#include "Prol16ExeFile.h"
#include "ScopedFileStream.h"

#include <istream>
#include <ostream>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class Disassembler final : private ::util::NonCopyable {
public:
	using Immediate = util::Immediate;
	using Instruction = util::Instruction;
	using Address = PROL16::util::memory::Address;
	using CodeSegment = util::Prol16ExeFile::CodeSegment;

	using SourceStream = ::util::ScopedFileStream<std::ifstream>;

	Disassembler(SourceStream &sourceStream, std::ostream &destinationStream);

	void disassemble();

private:
	util::Prol16ExeFile prol16ExeFile;
	std::ostream &destinationStream;
};

}	// namespace PROL16

#endif /* PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_DISASSEMBLER_H_INCLUDED */
