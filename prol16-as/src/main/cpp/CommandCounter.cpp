/**
 * @author		creiterer
 * @date 		2019-03-30
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "CommandCounter.h"

namespace PROL16 {	// NOLINT(readability-identifier-naming)

CommandCounter& CommandCounter::operator++() {
	// Beware that the memory has a width of 16 bit / 2 byte
	// -> only increment by one, not by sizeof(Instruction::EncodedType), which is 2
	++counter;

	return *this;
}

// NOLINTNEXTLINE(readability-const-return-type)
CommandCounter const CommandCounter::operator++(int) {
	CommandCounter tmp(*this);
	operator++();

	return tmp;
}

CommandCounter& CommandCounter::operator+=(uint16_t const rhs) {
	// Beware that the memory has a width of 16 bit / 2 byte
	// -> only add rhs, not rhs * sizeof(Instruction::EncodedType)
	counter += rhs;

	return *this;
}

} 	// namespace PROL16
