/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing errors that occur during PROL16 instruction decoding.
 */

#include "InstructionDecodeError.h"

#include <ios>
#include <sstream>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

InstructionDecodeError::InstructionDecodeError(Instruction::EncodedType const encodedValue, std::string const &hint) {
	std::ostringstream errorMessageStream;

	errorMessageStream << "failed to decode instruction " << std::hex << std::showbase << encodedValue << ": " << hint;

	errorMessage = errorMessageStream.str();
}

char const* InstructionDecodeError::what() const noexcept {
	return errorMessage.c_str();
}

}	// namespace util
}	// namespace PROL16
