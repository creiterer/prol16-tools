/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Instruction.h"

#include "InstructionDecodeError.h"

#include <sstream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

Instruction Instruction::decode(EncodedType const encodedValue) {
	try {
		Instruction instruction(decodeOpcode(encodedValue), decodeRa(encodedValue), decodeRb(encodedValue));
		return instruction;
	} catch (std::exception const &e) {
		throw util::InstructionDecodeError(encodedValue, e.what());
	}
}

Instruction::Instruction(Opcode const opcode)
: rb(0), ra(0), opcode(util::validateOpcode(opcode)) {

}

Instruction::Instruction(Mnemonic const mnemonic)
: rb(0), ra(0), opcode(util::validateOpcode(util::getOpcodeOfMnemonic(mnemonic))) {

}

Instruction::Instruction(Opcode const opcode, Register const ra)
: rb(0), ra(util::validateRegister(ra)), opcode(util::validateOpcode(opcode)) {

}

Instruction::Instruction(Mnemonic const mnemonic, Register const ra)
: rb(0), ra(util::validateRegister(ra)), opcode(util::validateOpcode(util::getOpcodeOfMnemonic(mnemonic))) {

}

Instruction::Instruction(Opcode const opcode, Register const ra, Register const rb)
: rb(util::validateRegister(rb)), ra(util::validateRegister(ra)), opcode(util::validateOpcode(opcode)) {

}

Instruction::Instruction(Mnemonic const mnemonic, Register const ra, Register const rb)
: rb(util::validateRegister(rb)), ra(util::validateRegister(ra)), opcode(util::validateOpcode(util::getOpcodeOfMnemonic(mnemonic))) {

}

Instruction::operator Instruction::EncodedType() const {
	return encode();
}

Instruction::EncodedType Instruction::encode() const {
	EncodedType value = encodeRb() | encodeRa() | encodeOpcode();

	return value;
}

std::string Instruction::asString() const {
	using namespace util;

	Mnemonic const mnemonic = getMnemonicOfOpcode(opcode);

	std::ostringstream instructionStream;
	instructionStream << getMnemonicAsString(mnemonic);

	switch (numberOfRegisterOperands(mnemonic)) {
	case 0: break;
	case 1: instructionStream << ' ' << getCanonicalRegisterName(ra); break;
	case 2: instructionStream << ' ' << getCanonicalRegisterName(ra) << ", " << getCanonicalRegisterName(rb); break;
	}

	return instructionStream.str();
}

Instruction::EncodedType Instruction::encodeRb() const {
	return rb;
}

Instruction::EncodedType Instruction::encodeRa() const {
	return ra << RegisterBitWidth;
}

Instruction::EncodedType Instruction::encodeOpcode() const {
	return opcode << (2*RegisterBitWidth);
}

Instruction::Register Instruction::decodeRb(EncodedType const encodedValue) {
	return encodedValue & RegisterMask;
}

Instruction::Register Instruction::decodeRa(EncodedType const encodedValue) {
	return (encodedValue >> RegisterBitWidth) & RegisterMask;
}

Instruction::Opcode Instruction::decodeOpcode(EncodedType const encodedValue) {
	return (encodedValue >> (2*RegisterBitWidth)) & OpcodeMask;
}

} 	// namespace util
} 	// namespace PROL16

std::ostream& operator<<(std::ostream &stream, PROL16::util::Instruction const &instruction) {
	stream << instruction.asString();
	return stream;
}

util::logging::Logger& operator<<(util::logging::Logger &logger, PROL16::util::Instruction const &instruction) {
	logger << instruction.asString();
	return logger;
}
