/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing a PROL16 instruction.
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_INSTRUCTION_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_INSTRUCTION_H_INCLUDED

#include "Logger.h"
#include "MnemonicUtils.h"
#include "RegisterUtils.h"

#include <cstdint>
#include <ostream>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class Instruction final {
public:
	using EncodedType = uint16_t;
	using Register = util::Register;
	using Opcode = util::Opcode;
	using Mnemonic = util::Mnemonic;

	static unsigned const RegisterBitWidth = 5;
	static unsigned const OpcodeBitWidth = 6;

	static Instruction decode(EncodedType const encodedValue);

	Instruction() = default;
	explicit Instruction(Opcode const opcode);
	explicit Instruction(Mnemonic const mnemonic);
	Instruction(Opcode const opcode, Register const ra);
	Instruction(Mnemonic const mnemonic, Register const ra);
	Instruction(Opcode const opcode, Register const ra, Register const rb);
	Instruction(Mnemonic const mnemonic, Register const ra, Register const rb);

	// NOLINTNEXTLINE(google-explicit-constructor)
	operator EncodedType() const;

	inline Register getRb() const { return rb; }
	inline Register getRa() const { return ra; }
	inline Opcode getOpcode() const { return opcode; }
	inline Mnemonic getMnemonic() const { return util::getMnemonicOfOpcode(opcode); }
	inline std::string getMnemonicString() const { return util::getMnemonicAsString(getMnemonic()); }

	EncodedType encode() const;

	std::string asString() const;

	inline bool is(util::Mnemonic const mnemonic) const { return opcode == mnemonic; }

private:
	static EncodedType const RegisterMask = 0x001F;
	static EncodedType const OpcodeMask = 0x003F;

	Register rb : RegisterBitWidth;			// bits 0 -- 4
	Register ra : RegisterBitWidth;			// bits 5 -- 9
	Opcode opcode : OpcodeBitWidth;			// bits 10 -- 15

	static Register decodeRb(EncodedType const encodedValue);
	static Register decodeRa(EncodedType const encodedValue);
	static Opcode decodeOpcode(EncodedType const encodedValue);

	EncodedType encodeRb() const;
	EncodedType encodeRa() const;
	EncodedType encodeOpcode() const;
};

} 	// namespace util
} 	// namespace PROL16

std::ostream& operator<<(std::ostream &stream, PROL16::util::Instruction const &instruction);
util::logging::Logger& operator<<(util::logging::Logger &logger, PROL16::util::Instruction const &instruction);

#endif /* PROL16_AS_SRC_MAIN_CPP_INSTRUCTION_H_INCLUDED */
