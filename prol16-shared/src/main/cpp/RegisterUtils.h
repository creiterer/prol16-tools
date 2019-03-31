/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Some register utility functions.
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_REGISTERUTILS_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_REGISTERUTILS_H_INCLUDED

#include <cstdint>
#include <string>

namespace PROL16 { namespace util {

using Register = uint8_t;

static Register const RegisterCount = 16;

bool isRegisterValid(Register const reg);

Register validateRegister(Register const reg);

void checkRegisterIsValid(Register const reg);

void checkRegistersAreValid(Register const reg);

template <typename... Registers>
void checkRegistersAreValid(Register const reg, Registers const... registers) {
	checkRegisterIsValid(reg);
	checkRegistersAreValid(registers...);
}

Register parseRegisterNumber(std::string const &registerName);

Register parseRegisterNumberChecked(std::string const &registerName);

}}

#endif /* PROL16_AS_SRC_MAIN_CPP_REGISTERUTILS_H_INCLUDED */
