/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Error class for incomplete PROL16 instructions.
 */

#include "IncompleteInstructionError.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

IncompleteInstructionError::IncompleteInstructionError() {
	errorMessage = "failed to read a complete instruction";
}

IncompleteInstructionError::IncompleteInstructionError(std::string const &hint) : IncompleteInstructionError() {
	errorMessage.append(": ").append(hint);
}

char const* IncompleteInstructionError::what() const noexcept {
	return errorMessage.c_str();
}

}	// namespace util
}	// namespace PROL16
