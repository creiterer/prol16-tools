/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Error class for invalid registers.
 */

#include "RegisterError.h"

#include <sstream>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

RegisterError::RegisterError(Register const reg) {
	std::ostringstream errorMessageStream;

	// the cast is necessary because uint8_t is interpreted as character and not as number!
	errorMessageStream << "register 'r" << static_cast<unsigned>(reg) << "' is out of the range of allowed registers (rpc, rra, rsp, rfp, r4 -- r" << RegisterCount-1 << ')';
	errorMessage = errorMessageStream.str();
}

RegisterError::RegisterError(std::string const &registerName) {
	std::ostringstream errorMessageStream;

	errorMessageStream << "register '" << registerName << "' is not a valid register (rpc, rra, rsp, rfp, r4 -- r" << RegisterCount-1 << ')';
	errorMessage = errorMessageStream.str();
}

char const* RegisterError::what() const noexcept {
	return errorMessage.c_str();
}

}	// namespace util
}	// namespace PROL16
