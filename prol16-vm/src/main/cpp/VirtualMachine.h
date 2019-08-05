/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_VIRTUAL_MACHINE_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_VIRTUAL_MACHINE_H_INCLUDED

#include <cstdint>
#include <ios>

#include "NonCopyable.h"
#include "VirtualMemory.h"
#include "RegisterFile.h"

#include "Instruction.h"
#include "RegisterUtils.h"
#include "NumberUtils.h"
#include "Flag.h"

namespace PROL16 {

class VirtualMachine final : private ::util::NonCopyable {
public:
	using Register = util::Register;
	using Immediate = util::Immediate;
	using ArithmeticResult = uint32_t;

	static uint8_t const BitWidth = 16;

	VirtualMachine(std::string const &filename, bool const verboseLogging);
	~VirtualMachine() = default;

	void run();

private:
	VirtualMemory::Address programCounter;
	VirtualMemory memory;
	RegisterFile registerFile;
	Flag carryFlag;
	Flag zeroFlag;
	bool const verboseLogging;

	Instruction fetchAndDecodeInstruction();
	Immediate fetchImmediate();
	bool executeInstruction(Instruction const &instruction);

	void setProgramCounter(VirtualMemory::Address const address);
	void setZeroFlag(RegisterFile::Data const result);
	void setCarryFlag(ArithmeticResult const result);

	void executeAdd(Register const ra, Register const rb, bool const withCarry = false);
	void executeSub(Register const ra, Register const rb, bool const withCarry = false, bool const storeResult = true);
	void executeInc(Register const ra);
	void executeDec(Register const ra);
	void executeShl(Register const ra, bool const withCarry = false);
	void executeShr(Register const ra, bool const withCarry = false);

	void printInfo(std::string const &message) const;
	void printProgramCounter(std::ostream &stream) const;
};

}

#endif
