/**
 * @author		creiterer
 * @date 		2019-03-30
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_COMMANDCOUNTER_H_INCLUDED
#define PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_COMMANDCOUNTER_H_INCLUDED

#include "Instruction.h"

#include <cstdint>

namespace PROL16 {	// NOLINT(readability-identifier-naming)

class CommandCounter final {
public:
	using Counter = uint16_t;

	CommandCounter() = default;

	CommandCounter& operator++();
	CommandCounter const operator++(int);

	CommandCounter& operator+=(uint16_t const rhs);

	friend CommandCounter operator+(CommandCounter lhs, uint16_t const rhs) {
		lhs += rhs;
		return lhs;
	}

	inline Counter getNextInstructionAddress() const { return counter; }

private:
	Counter counter = 0;
};

} 	// namespace PROL16

#endif /* PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_COMMANDCOUNTER_H_INCLUDED */
