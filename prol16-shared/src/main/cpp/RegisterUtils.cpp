/**
 * @author		creiterer
 * @date 		2019-03-15
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Some register utility functions.
 */

#include "RegisterUtils.h"

#include "RegisterError.h"
#include "StringUtils.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

namespace {

using RegisterNameTable = std::unordered_map<std::string, Register>;

// ATTENTION: keep in sync with 'PROL16RegisterInfo.td'
RegisterNameTable const SpecialRegisterTable = {		// NOLINT(cert-err58-cpp)
		{"rsp", 0},
		{"rfp", 1},
		{"rra", 2}
};

}	// anonymous namespace

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

std::string getCanonicalRegisterName(Register const reg) {
	checkRegisterIsValid(reg);

	// for now, only use special register name for 'rsp'
	if (reg == 0) {
		return "rsp";
	}

	std::ostringstream registerNameStream;
	// the cast is necessary because uint8_t is interpreted as character and not as number!
	registerNameStream << 'r' << static_cast<unsigned>(reg);

	return registerNameStream.str();
}

bool isSpecialRegister(std::string const &registerName) {
	return SpecialRegisterTable.find(getCanonicalRegisterName(registerName)) != SpecialRegisterTable.cend();
}

bool isSpecialRegister(Register const reg) {
	return std::any_of(SpecialRegisterTable.cbegin(), SpecialRegisterTable.cend(), [reg](RegisterNameTable::value_type const &value) {
		return value.second == reg;
	});
}

bool isReturnAddressRegister(std::string const &registerName) {
	std::string const loweredRegisterName = ::util::toLower(registerName);

	return (loweredRegisterName == "ra") || (loweredRegisterName == "rra");
}

Register parseRegisterNumber(std::string const &registerName) {
	::util::preconditions::checkStringIsNotEmpty(registerName);
	std::string const canonicalRegisterName = getCanonicalRegisterName(registerName);

	if (isSpecialRegister(canonicalRegisterName)) {
		return SpecialRegisterTable.at(::util::toLower(canonicalRegisterName));
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

}	// namespace util
}	// namespace PROL16
