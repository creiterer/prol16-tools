/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing errors that occur during PROL16 instruction decoding.
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_INSTRUCTIONDECODEERROR_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_INSTRUCTIONDECODEERROR_H_INCLUDED

#include "Instruction.h"

#include <stdexcept>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class InstructionDecodeError final : public std::exception {
public:
	InstructionDecodeError(Instruction::EncodedType const encodedValue, std::string const &hint);

	char const* what() const noexcept override;

private:
	std::string errorMessage;
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_INSTRUCTIONDECODEERROR_H_INCLUDED */
