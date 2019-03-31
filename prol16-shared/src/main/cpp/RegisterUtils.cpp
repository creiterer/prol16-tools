/**
 * @author		creiterer
 * @date 		2019-03-15
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Some register utility functions.
 */

#include "RegisterUtils.h"

#include <unordered_map>
#include <stdexcept>

#include "RegisterError.h"
#include "StringUtils.h"

namespace PROL16 { namespace util {

namespace {

std::unordered_map<std::string, Register> const specialRegisterTable = {
		{"rsp", 0},
		{"rfp", 1},
		{"rra", 2}
};

}

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

bool isSpecialRegister(std::string const &registerName) {
	return specialRegisterTable.find(::util::toLower(registerName)) != specialRegisterTable.cend();
}

Register parseRegisterNumber(std::string const &registerName) {
	if (isSpecialRegister(registerName)) {
		return specialRegisterTable.at(::util::toLower(registerName));
	}

	return std::stoul(std::string(registerName.cbegin()+1, registerName.cend()));
}

Register parseRegisterNumberChecked(std::string const &registerName) {
	try {
		Register const registerNumber = parseRegisterNumber(registerName);
		checkRegisterIsValid(registerNumber);

		return registerNumber;
	} catch (std::invalid_argument const&) {
		throw RegisterError(registerName);
	}
}

}}
