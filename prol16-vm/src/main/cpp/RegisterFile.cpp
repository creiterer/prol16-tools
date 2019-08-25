/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "RegisterFile.h"

#include <sstream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

RegisterFile::Data const RegisterFile::MagicInitValue;

RegisterFile::RegisterFile() {
	registerFile.fill(MagicInitValue);
}

RegisterFile::Data& RegisterFile::operator[](Register const reg) {
	util::checkRegisterIsValid(reg);

	return registerFile.at(reg);
}

RegisterFile::Data RegisterFile::operator[](Register const reg) const {
	util::checkRegisterIsValid(reg);

	return registerFile.at(reg);
}

RegisterFile::Data RegisterFile::read(Register const reg) const {
	util::checkRegisterIsValid(reg);

	return registerFile.at(reg);
}

void RegisterFile::write(Register const reg, Data const data) {
	util::checkRegisterIsValid(reg);

	registerFile.at(reg) = data;
}

}	// namespace PROL16
