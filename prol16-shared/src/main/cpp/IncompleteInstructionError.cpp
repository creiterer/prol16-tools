/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "IncompleteInstructionError.h"

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

}}
