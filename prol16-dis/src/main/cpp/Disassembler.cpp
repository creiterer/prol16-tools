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
		Instruction instruction = Instruction::decode(codeSegment.at(address));

		util::printHexNumberFormatted(destinationStream, address) << ":\t";
		destinationStream << instruction;

		if (instruction.is(util::LOADI)) {
			try {
				Immediate const immediate = codeSegment.at(++address);
				util::printHexNumberFormatted(destinationStream << ", ", immediate) << 'h' << std::endl;
			} catch (std::out_of_range const&) {
				throw util::IncompleteInstructionError("failed to read immediate of '" + instruction.getMnemonicString() + "'");
			}
		} else {
			destinationStream << std::endl;
		}
	}
}

}	// namespace PROL16
