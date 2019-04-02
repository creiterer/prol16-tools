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

std::string getCanonicalRegisterName(std::string const &registerName) {
	::util::preconditions::checkStringIsNotEmpty(registerName);

	std::string loweredRegisterName = ::util::toLower(registerName);

	if ((loweredRegisterName.at(0) != 'r') || (loweredRegisterName == "ra")) {
		::util::prepend(loweredRegisterName, 'r');
	}

	return loweredRegisterName;
}

bool isSpecialRegister(std::string const &registerName) {
	return specialRegisterTable.find(getCanonicalRegisterName(registerName)) != specialRegisterTable.cend();
}

bool isReturnAddressRegister(std::string const &registerName) {
	std::string const loweredRegisterName = ::util::toLower(registerName);

	return (loweredRegisterName == "ra") || (loweredRegisterName == "rra");
}

Register parseRegisterNumber(std::string const &registerName) {
	::util::preconditions::checkStringIsNotEmpty(registerName);
	std::string const canonicalRegisterName = getCanonicalRegisterName(registerName);

	if (isSpecialRegister(canonicalRegisterName)) {
		return specialRegisterTable.at(::util::toLower(canonicalRegisterName));
	}

	return std::stoul(std::string(canonicalRegisterName.cbegin()+1, canonicalRegisterName.cend()));
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
