/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_OPCODEERROR_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_OPCODEERROR_H_INCLUDED

#include <stdexcept>
#include <string>

#include "MnemonicUtils.h"

namespace PROL16 { namespace util {

class OpcodeError final : public std::exception {
public:
	OpcodeError(Opcode const opcode);

	char const* what() const noexcept override;

private:
	std::string errorMessage;
};

}}

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_OPCODEERROR_H_INCLUDED */
