/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing the PROL16 register file.
 */

#include "RegisterFile.h"

#include <sstream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

RegisterFile::Data const RegisterFile::MagicInitValue;

RegisterFile::RegisterFile(Data const initialStackPointerValue) {
	registerFile.fill(MagicInitValue);
	writeStackPointer(initialStackPointerValue);
	writeFramePointer(initialStackPointerValue);
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

RegisterFile::Data& RegisterFile::getProgramCounter() {
	return registerFile.at(util::getProgramCounterRegister());
}

RegisterFile::Data RegisterFile::readProgramCounter() const {
	return read(util::getProgramCounterRegister());
}

void RegisterFile::writeProgramCounter(Data const data) {
	write(util::getProgramCounterRegister(), data);
}

RegisterFile::Data RegisterFile::readReturnAddress() const {
	return read(util::getReturnAddressRegister());
}

RegisterFile::Data RegisterFile::readStackPointer() const {
	return read(util::getStackPointerRegister());
}

void RegisterFile::writeStackPointer(Data const data) {
	write(util::getStackPointerRegister(), data);
}

RegisterFile::Data RegisterFile::readFramePointer() const {
	return read(util::getFramePointerRegister());
}

void RegisterFile::writeFramePointer(Data const data) {
	write(util::getFramePointerRegister(), data);
}

}	// namespace PROL16
