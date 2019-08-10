/**
 * @author		creiterer
 * @date 		2019-03-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "MnemonicUtils.h"

#include <unordered_map>
#include <stdexcept>
#include <sstream>

#include "OpcodeError.h"

namespace PROL16 { namespace util {

namespace {

std::unordered_map<Mnemonic, std::string> const mnemonicStringTable = {
		{NOP, "nop"},
		{SLEEP, "sleep"},
		{LOADI, "loadi"},
		{LOAD, "load"},
		{STORE, "store"},
		{MOVE, "move"},
		{JUMP, "jump"},
		{JUMPC, "jumpc"},
		{JUMPZ, "jumpz"},
		{AND, "and"},
		{OR, "or"},
		{XOR, "xor"},
		{NOT, "not"},
		{ADD, "add"},
		{ADDC, "addc"},
		{SUB, "sub"},
		{SUBC, "subc"},
		{COMP, "comp"},
		{INC, "inc"},
		{DEC, "dec"},
		{SHL, "shl"},
		{SHR, "shr"},
		{SHLC, "shlc"},
		{SHRC, "shrc"},
		{PRINT, "print"},
		{PRINTI, "print"}	// for convenience, also use 'print' for mnemonic/opcode 'PRINTI', like the assembler does
};

}

bool isOpcodeValid(Opcode const opcode) {
	Mnemonic const mnemonic = getMnemonicOfOpcode(opcode);

	return mnemonicStringTable.find(mnemonic) != mnemonicStringTable.cend();
}

Opcode validateOpcode(Opcode const opcode) {
	if (!isOpcodeValid(opcode)) {
		throw OpcodeError(opcode);
	}

	return opcode;
}

std::string getMnemonicStringOfOpcode(Opcode const opcode) {
	return mnemonicStringTable.at(getMnemonicOfOpcode(opcode));
}

Mnemonic getMnemonicOfOpcode(Opcode const opcode) {
	return static_cast<Mnemonic>(opcode);
}

Opcode getOpcodeOfMnemonic(Mnemonic const mnemonic) {
	return static_cast<Opcode>(mnemonic);
}

std::string getMnemonicAsString(Mnemonic const mnemonic) {
	return mnemonicStringTable.at(mnemonic);
}

uint8_t numberOfRegisterOperands(Mnemonic const mnemonic) {
	switch (mnemonic) {
	case NOP:
	case SLEEP:
	case PRINTI:
		return 0;

	case LOADI:
	case JUMP:
	case JUMPC:
	case JUMPZ:
	case NOT:
	case INC:
	case DEC:
	case SHL:
	case SHR:
	case SHLC:
	case SHRC:
	case PRINT:
		return 1;

	case LOAD:
	case STORE:
	case MOVE:
	case AND:
	case OR:
	case XOR:
	case ADD:
	case ADDC:
	case SUB:
	case SUBC:
	case COMP:
		return 2;

	default: {
		std::ostringstream errorMessage;
		errorMessage << "invalid mnemonic value: " << mnemonic;
		throw std::invalid_argument(errorMessage.str());
	}
	}
}

uint8_t numberOfRegisterOperands(Opcode const opcode) {
	return numberOfRegisterOperands(getMnemonicOfOpcode(opcode));
}

}}
