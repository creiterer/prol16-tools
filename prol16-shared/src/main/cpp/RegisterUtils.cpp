/**
 * @author		creiterer
 * @date 		2019-03-15
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Some register utility functions.
 */

#include "RegisterUtils.h"

#include "RegisterError.h"

namespace PROL16 { namespace util {

bool isRegisterValid(Register const reg) {
	return reg < RegisterCount;
}

Register validateRegister(Register const reg) {
	if (!isRegisterValid(reg)) {
		throw RegisterError(reg);
	}

	return reg;
}

void checkRegisterIsValid(Register const reg) {
	validateRegister(reg);
}

void checkRegistersAreValid(Register const reg) {
	checkRegisterIsValid(reg);
}

Register parseRegisterNumber(std::string const &registerName) {
	return std::stoul(std::string(registerName.cbegin()+1, registerName.cend()));
}

Register parseRegisterNumberChecked(std::string const &registerName) {
	Register const registerNumber = parseRegisterNumber(registerName);
	checkRegisterIsValid(registerNumber);

	return registerNumber;
}

}}
