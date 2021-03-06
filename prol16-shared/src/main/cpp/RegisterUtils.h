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
#include <utility>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

using Register = uint8_t;
using RegisterPair = std::pair<Register, Register>;

constexpr Register RegisterCount = 32;

bool isRegisterValid(Register const reg);

Register validateRegister(Register const reg);

void checkRegisterIsValid(Register const reg);

void checkRegistersAreValid(Register const reg);

template <typename... Registers>
void checkRegistersAreValid(Register const reg, Registers const... registers) {
	checkRegisterIsValid(reg);
	checkRegistersAreValid(registers...);
}

/**
 * TODO
 * @param registerName
 * @return
 */
std::string getCanonicalRegisterName(std::string const &registerName);

std::string getCanonicalRegisterName(Register const reg);

Register getProgramCounterRegister();

Register getReturnAddressRegister();

Register getStackPointerRegister();

Register getFramePointerRegister();

/**
 * TODO
 * @param registerName
 * @return
 */
bool isSpecialRegister(std::string const &registerName);

bool isSpecialRegister(Register const reg);

bool isReturnAddressRegister(std::string const &registerName);

/**
 * TODO
 * @param registerName
 * @return
 */
Register parseRegisterNumber(std::string const &registerName);

Register parseRegisterNumberChecked(std::string const &registerName);

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_AS_SRC_MAIN_CPP_REGISTERUTILS_H_INCLUDED */
