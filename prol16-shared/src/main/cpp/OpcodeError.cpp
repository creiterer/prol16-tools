/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "OpcodeError.h"

#include <sstream>
#include <ios>

namespace PROL16 { namespace util {

OpcodeError::OpcodeError(Opcode const opcode) {
	std::ostringstream errorMessageStream;

	// the cast is necessary because uint8_t is interpreted as character and not as number!
	errorMessageStream << "invalid opcode: " << std::hex << std::showbase << static_cast<unsigned>(opcode);

	errorMessage = errorMessageStream.str();
}

char const* OpcodeError::what() const noexcept {
	return errorMessage.c_str();
}

}}
