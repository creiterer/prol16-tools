/**
 * @author		creiterer
 * @date 		2019-03-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_MNEMONICUTILS_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_MNEMONICUTILS_H_INCLUDED

#include <cstdint>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

using Opcode = uint8_t;

// NOTE: max. value with 6 bit is '11 1111' which is '0x3F'
// -> specifying '0xFF' for 'PRINTI' is wrong because decoding leads to '0x3F'
// so that decoding wouldn't find a corresponding opcode/mnemonic and result in
// an invalid opcode error!
enum Mnemonic : Opcode {
	NOP = 0x0,
	SLEEP = 0x1,
	LOADI = 0x2,
	LOAD = 0x3,
	STORE = 0x4,
	MOVE = 0xC,
	JUMP = 0x8,
	JUMPC = 0xA,
	JUMPZ = 0xB,
	AND = 0x10,
	OR = 0x11,
	XOR = 0x12,
	NOT = 0x13,
	ADD = 0x14,
	ADDC = 0x15,
	SUB = 0x16,
	SUBC = 0x17,
	COMP = 0x18,
	INC = 0x1A,
	DEC = 0x1B,
	SHL = 0x1C,
	SHR = 0x1D,
	SHLC = 0x1E,
	SHRC = 0x1F,
};

bool isOpcodeValid(Opcode const opcode);

Opcode validateOpcode(Opcode const opcode);

std::string getMnemonicStringOfOpcode(Opcode const opcode);

Mnemonic getMnemonicOfOpcode(Opcode const opcode);

Opcode getOpcodeOfMnemonic(Mnemonic const mnemonic);

std::string getMnemonicAsString(Mnemonic const mnemonic);

uint8_t numberOfRegisterOperands(Mnemonic const mnemonic);

uint8_t numberOfRegisterOperands(Opcode const opcode);

bool isAnyJump(Mnemonic const mnemonic);

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_MNEMONICUTILS_H_INCLUDED */
