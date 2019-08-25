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

#include <iomanip>
#include <iostream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

Disassembler::Disassembler(std::istream &sourceStream, std::ostream &destinationStream)
: sourceStream(sourceStream), destinationStream(destinationStream) {

}

void Disassembler::disassemble() {
	try {
		uint16_t address = 0;
		Instruction instruction = readAndDecodeInstruction();

		while (!sourceStream.eof() && !sourceStream.fail()) {
			util::printHexNumberFormatted(destinationStream, address) << ":\t";
			destinationStream << instruction;

			if (instruction.is(util::LOADI) || instruction.is(util::PRINTI)) {
				Immediate const immediate = readImmediate();

				if (instruction.is(util::PRINTI)) {
					util::printHexNumberFormatted(destinationStream << " ", immediate) << 'h' << std::endl;
				} else {
					util::printHexNumberFormatted(destinationStream << ", ", immediate) << 'h' << std::endl;
				}

				address += 2;
			} else {
				destinationStream << std::endl;
				++address;
			}
			// read next instruction
			instruction = readAndDecodeInstruction();
		}
	} catch (::util::EOFError const&) {
		// reached end-of-file -> disassembling finished
	}
}

Instruction Disassembler::readAndDecodeInstruction() {
	unsigned const bufferSize = sizeof(Instruction::EncodedType)/sizeof(char);
	char instructionBuffer[bufferSize];

	sourceStream.read(instructionBuffer, bufferSize);

	if ((sourceStream.gcount() > 0) && (sourceStream.gcount() < bufferSize)) {
		// we read something, but not a complete instruction
		throw util::IncompleteInstructionError();
	}

	if ((sourceStream.gcount() == 0) && sourceStream.eof()) {
		// we reached end-of-file
		throw ::util::EOFError();
	}

	if (sourceStream.gcount() != bufferSize) {
		// we read more than bufferSize or gcount is 0 but we are not at EOF -> either case is weird
		throw std::runtime_error("failed to read instruction");
	}

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	Instruction::EncodedType const encodedValue = *reinterpret_cast<Instruction::EncodedType*>(instructionBuffer);
	return Instruction::decode(encodedValue);
}

Disassembler::Immediate Disassembler::readImmediate() {
	unsigned const bufferSize = sizeof(Immediate)/sizeof(char);
	char immediateBuffer[bufferSize];

	sourceStream.read(immediateBuffer, bufferSize);

	if (sourceStream.gcount() != bufferSize) {
		throw util::IncompleteInstructionError("failed to read loadi's immediate");
	}

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	Immediate const immediate = *reinterpret_cast<Immediate*>(immediateBuffer);
	return immediate;
}

}	// namespace PROL16
