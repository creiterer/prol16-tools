/**
 * @author		creiterer
 * @date 		2019-03-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Disassembler.h"

#include "EOFError.h"
#include "IncompleteInstructionError.h"
#include "MnemonicUtils.h"
#include "Prol16ExeFileWriter.h"

#include <array>
#include <iomanip>
#include <iostream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

Disassembler::Disassembler(SourceStream &sourceStream, std::ostream &destinationStream)
: prol16ExeFile(util::Prol16ExeFile::parse(sourceStream)), destinationStream(destinationStream) {

}

void Disassembler::disassemble() {
	Address const entryPointAddress = prol16ExeFile.getEntryPointAddress();
	util::printHexNumberFormatted(destinationStream << "entry point address: ", entryPointAddress) << '\n';

	CodeSegment const codeSegment = prol16ExeFile.getCodeSegment();

	// NOLINTNEXTLINE(bugprone-too-small-loop-variable)
	for (Address address = 0; address < codeSegment.size(); ++address) {
		// skip the PROL16 standard library magic marker,
		// which would result in an invalid instruction
		if ((codeSegment.at(address) == util::Prol16ExeFileWriter::MagicStdLibValue) &&
			(codeSegment.at(address+1) == Instruction(util::PRINT, 4))) {
			continue;
		}

		Instruction instruction = Instruction::decode(codeSegment.at(address));

		util::printHexNumberFormatted(destinationStream, address) << ":\t";
		destinationStream << instruction;

		if (instruction.is(util::LOADI) || instruction.is(util::PRINTI)) {
			try {
				Immediate const immediate = codeSegment.at(++address);

				if (instruction.is(util::PRINTI)) {
					util::printHexNumberFormatted(destinationStream << " ", immediate) << 'h' << std::endl;
				} else {
					util::printHexNumberFormatted(destinationStream << ", ", immediate) << 'h' << std::endl;
				}
			} catch (std::out_of_range const&) {
				throw util::IncompleteInstructionError("failed to read immediate of '" + instruction.getMnemonicString() + "'");
			}
		} else {
			destinationStream << std::endl;
		}
	}
}

}	// namespace PROL16
