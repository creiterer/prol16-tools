/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_VIRTUAL_MACHINE_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_VIRTUAL_MACHINE_H_INCLUDED

#include "Flag.h"
#include "RegisterFile.h"
#include "VirtualMemory.h"

#include "ArithmeticResult.h"
#include "CommandInterpreter.h"
#include "Instruction.h"
#include "Logger.h"
#include "MnemonicUtils.h"
#include "NonCopyable.h"
#include "NumberUtils.h"
#include "RegisterUtils.h"
#include "RuntimeLibrary.h"
#include "SymbolTable.h"

#include <cstdint>
#include <ios>
#include <memory>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class VirtualMachine final : private ::util::NonCopyable {
public:
	using Register = util::Register;
	using RegisterPair = util::RegisterPair;
	using Mnemonic = util::Mnemonic;
	using Immediate = util::Immediate;
	using Address = VirtualMemory::Address;
	using Data = VirtualMemory::Data;
	using ArithmeticResult = util::ArithmeticResult;
	using ArithmeticResultType = ArithmeticResult::ResultType;
	using Instruction = util::Instruction;

	static uint8_t const BitWidth = 16;
	static size_t const InstructionLogWidth = 20;

	VirtualMachine(std::string const &filename, ::util::logging::Logger &logger,
				   bool const interactive, bool const shouldPrintDecimal);

	void run();

private:
	RegisterFile registerFile;
	VirtualMemory memory;
	Flag carryFlag;
	Flag zeroFlag;
	VirtualMemory::Address &programCounter;
	util::SymbolTable symbolTable;
	::util::logging::Logger &logger;
	std::unique_ptr<::util::CommandInterpreter> commandInterpreter;
	bool const shouldPrintDecimal;

	Instruction fetchAndDecodeInstruction();
	Immediate fetchImmediate();
	bool executeInstruction(Instruction const &instruction);

	void setProgramCounter(VirtualMemory::Address const address);
	void setZeroFlag(RegisterFile::Data const result);
	void setCarryFlag(ArithmeticResult const &result);

	void executeAdd(Register const ra, Register const rb, bool const withCarry = false);
	void executeSub(Register const ra, Register const rb, bool const withCarry = false, bool const storeResult = true);
	void executeInc(Register const ra);
	void executeDec(Register const ra);
	void executeShl(Register const ra, bool const withCarry = false);
	void executeShr(Register const ra, bool const withCarry = false);
	void executeRuntimeLibFunction(Address const address);
	void executeMul(RegisterPair const &srcRegs,  RegisterPair const &destRegs);

	void printInfo(std::string const &message) const;
	void printProgramCounter(std::ostream &stream) const;
	void printState(std::ostream &stream) const;
	void printInstructionOperandValues(std::ostream &stream, Mnemonic const mnemonic,
									   Register const ra, Register const rb) const;
	std::ostream& printRegisterValue(std::ostream &stream, Register const ra) const;
	std::ostream& printMemoryValue(std::ostream &stream, Address const address) const;

	template <typename T>
	std::ostream& printData(std::ostream &stream, T const data) const;

	void logRuntimeLibCall(rtlib::RuntimeLibFunctionAddress const address);

	void setupCommandInterpreter();
	void printMemoryCommand(::util::CommandInterpreter::ArgumentVector const &arguments) const;
	void printRegisterCommand(::util::CommandInterpreter::ArgumentVector const &arguments) const;
};

}	// namespace PROL16

#endif
