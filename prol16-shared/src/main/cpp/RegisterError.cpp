/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "RegisterError.h"

#include <sstream>

namespace PROL16 { namespace util {

RegisterError::RegisterError(Register const reg) {
	std::ostringstream errorMessageStream;

	errorMessageStream << "register r" << reg << " is out of the range of allowed registers (r0 -- r" << RegisterCount-1 << ")";
	errorMessage = errorMessageStream.str();
}

char const* RegisterError::what() const noexcept {
	return errorMessage.c_str();
}

}}
