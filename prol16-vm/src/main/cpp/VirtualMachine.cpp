/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "VirtualMachine.h"

#include "OpcodeError.h"
#include "Prol16ExeFile.h"

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

using ::util::logging::Logger;

VirtualMachine::VirtualMachine(std::string const &filename, ::util::logging::Logger &logger)
: carryFlag("carry flag"), zeroFlag("zero flag"), programCounter(registerFile.getProgramCounter()), logger(logger) {
	util::Prol16ExeFile const p16ExeFile = util::Prol16ExeFile::parse(filename);

	// needs to be done before setting the program counter due to the
	// 'if (address >= memory.getCodeSegme' check
	memory.initializeCodeSegment(p16ExeFile.getCodeSegment());

	VirtualMemory::Address const entryPointAddress = p16ExeFile.getEntryPointAddress();
	setProgramCounter(entryPointAddress);

	logger << "starting program execution at address ";
	logger.forEachLogStream([entryPointAddress](Logger::LogStream stream){
		util::printHexNumberFormattedWithBase(stream, entryPointAddress);
	});
	logger << '\n';
}

void VirtualMachine::run() {
	bool stopProgramExecution = false;

	while ((programCounter < memory.getCodeSegmentSize()) && (!stopProgramExecution)) {
		Instruction instruction = fetchAndDecodeInstruction();
		stopProgramExecution = executeInstruction(instruction);
	}
}

VirtualMachine::Instruction VirtualMachine::fetchAndDecodeInstruction() {
	return Instruction::decode(memory[programCounter++]);
}

VirtualMachine::Immediate VirtualMachine::fetchImmediate() {
	return memory[programCounter++];
}

bool VirtualMachine::executeInstruction(Instruction const &instruction) {
	using namespace util;

	logger.forEachLogStream(std::bind(&VirtualMachine::printState, this, std::placeholders::_1));

	Mnemonic const mnemonic = instruction.getMnemonic();
	Register const ra = instruction.getRa();
	Register const rb = instruction.getRb();

	if (mnemonic != LOADI) {
		logger.setFormat(20, ' ', Logger::Adjustment::Left);
		logger << instruction;
		logger.restoreFormat();

		logger.forEachLogStream(std::bind(&VirtualMachine::printInstructionOperandValues, this, std::placeholders::_1, mnemonic, ra, rb));
	}

	switch (mnemonic) {
	case NOP: 	// no operation is performed
		break;

	case SLEEP: // stop program execution
		printInfo("stopping execution: reached 'sleep' instruction");
		return true;

	case LOADI: {
		Immediate const immediate = fetchImmediate();

		std::ostringstream instructionStream;
		instructionStream << instruction;
		printHexNumberFormattedWithBase(instructionStream << ", ", immediate);

		logger.setFormat(20, ' ', Logger::Adjustment::Left);
		logger << instructionStream.str();
		logger.restoreFormat();

		// printing of the register operand value has to happen before the register file gets updated
		// so that the value with which the instruction is executed is printed and not the value after
		// instruction execution
		logger.forEachLogStream(std::bind(&VirtualMachine::printInstructionOperandValues, this, std::placeholders::_1, mnemonic, ra, rb));

		registerFile[ra] = immediate;
		break;
	}

	case LOAD:
		registerFile[ra] = memory[registerFile[rb]];
		break;

	case STORE:
		memory[registerFile[rb]] = registerFile[ra];
		break;

	case MOVE:
		registerFile[ra] = registerFile[rb];
		break;

	case JUMP:
		setProgramCounter(registerFile[ra]);
		break;

	case JUMPC:
		if (carryFlag) {
			setProgramCounter(registerFile[ra]);
		}
		break;

	case JUMPZ:
		if (zeroFlag) {
			setProgramCounter(registerFile[ra]);
		}
		break;

	case AND:
		registerFile[ra] &= registerFile[rb];
		setZeroFlag(registerFile[ra]);
		carryFlag.reset();
		break;

	case OR:
		registerFile[ra] |= registerFile[rb];
		setZeroFlag(registerFile[ra]);
		carryFlag.reset();
		break;

	case XOR:
		registerFile[ra] ^= registerFile[rb];
		setZeroFlag(registerFile[ra]);
		carryFlag.reset();
		break;

	case NOT:
		registerFile[ra] = ~registerFile[ra];
		setZeroFlag(registerFile[ra]);
		carryFlag.reset();
		break;

	case ADD:
		executeAdd(ra, rb);
		break;

	case ADDC:
		executeAdd(ra, rb, true);
		break;

	case SUB:
		executeSub(ra, rb);
		break;

	case SUBC:
		executeSub(ra, rb, true);
		break;

	case COMP:
		executeSub(ra, rb, false, false);
		break;

	case INC:
		executeInc(ra);
		break;

	case DEC:
		executeDec(ra);
		break;

	case SHL:
		executeShl(ra);
		break;

	case SHR:
		executeShr(ra);
		break;

	case SHLC:
		executeShl(ra, true);
		break;

	case SHRC:
		executeShr(ra, true);
		break;

	case PRINT:
		if (!logger.isEnabled()) {
			printHexNumberFormattedWithBase(std::cout, registerFile[ra]);
			std::cout << '\n';
		}

		logger.forEachLogStream([this, ra](::util::logging::Logger::LogStream stream){
			printHexNumberFormattedWithBase(stream << '\n', registerFile[ra]);
		});

		break;

	case PRINTI: {
		Immediate const immediate = fetchImmediate();
		printHexNumberFormattedWithBase(std::cout, immediate);
		std::cout << '\n';

		logger << ", ";
		logger.forEachLogStream([immediate](::util::logging::Logger::LogStream stream){
			printHexNumberFormattedWithBase(stream, immediate);
		});
		break;
	}

	default:
		throw util::OpcodeError(instruction.getOpcode());
	}

	logger << '\n';

	return false;
}

void VirtualMachine::setProgramCounter(VirtualMemory::Address const address) {
	if (address >= memory.getCodeSegmentSize()) {
		std::ostringstream errorMessage;
		errorMessage << "trying to set program counter (";
		util::printHexNumberFormattedWithBase(errorMessage, programCounter) << ") ";
		errorMessage << "to an invalid address (";
		util::printHexNumberFormattedWithBase(errorMessage, address) << ")";

		throw std::runtime_error(errorMessage.str());
	}

	programCounter = address;
}

void VirtualMachine::setZeroFlag(RegisterFile::Data const result) {
	zeroFlag.set(result == 0);
}

void VirtualMachine::setCarryFlag(ArithmeticResult const result) {
	// if the 16th bit is set, there was an overflow/underflow -> set carry
	carryFlag.set((result & (1 << BitWidth)) != 0);
}

void VirtualMachine::executeAdd(Register const ra, Register const rb, bool const withCarry) {
	ArithmeticResult result = 0;
	if (withCarry) {
		result = static_cast<ArithmeticResult>(registerFile[ra]) + registerFile[rb] + (carryFlag ? 1 : 0);
	} else {
		result = static_cast<ArithmeticResult>(registerFile[ra]) + registerFile[rb];
	}

	registerFile[ra] = static_cast<RegisterFile::Data>(result);
	setZeroFlag(registerFile[ra]);
	setCarryFlag(result);
}

void VirtualMachine::executeSub(Register const ra, Register const rb, bool const withCarry, bool const storeResult) {
	ArithmeticResult result = 0;
	if (withCarry) {
		result = static_cast<ArithmeticResult>(registerFile[ra]) - registerFile[rb] - (carryFlag ? 1 : 0);
	} else {
		result = static_cast<ArithmeticResult>(registerFile[ra]) - registerFile[rb];
	}

	if (storeResult) {
		registerFile[ra] = static_cast<RegisterFile::Data>(result);
	}

	setZeroFlag(registerFile[ra]);
	setCarryFlag(result);
}

void VirtualMachine::executeInc(Register const ra) {
	ArithmeticResult result = 0;
	result = static_cast<ArithmeticResult>(registerFile[ra]) + 1;

	registerFile[ra] = static_cast<RegisterFile::Data>(result);
	setZeroFlag(registerFile[ra]);
	setCarryFlag(result);
}

void VirtualMachine::executeDec(Register const ra) {
	ArithmeticResult result = 0;
	result = static_cast<ArithmeticResult>(registerFile[ra]) - 1;

	registerFile[ra] = static_cast<RegisterFile::Data>(result);
	setZeroFlag(registerFile[ra]);
	setCarryFlag(result);
}

void VirtualMachine::executeShl(Register const ra, bool const withCarry) {
	carryFlag.set((registerFile[ra] & 0x8000) != 0);
	registerFile[ra] <<= 1;

	if (withCarry && carryFlag.isSet()) {
		registerFile[ra] |= 0x0001;	// shift in carry from the left -> set bit 0 to carry
	}

	setZeroFlag(registerFile[ra]);
}

void VirtualMachine::executeShr(Register const ra, bool const withCarry) {
	carryFlag.set((registerFile[ra] & 0x0001) != 0);
	registerFile[ra] >>= 1;

	if (withCarry && carryFlag.isSet()) {
		registerFile[ra] |= 0x8000;	// shift in carry from the right -> set bit 15 to carry
	}

	setZeroFlag(registerFile[ra]);
}

void VirtualMachine::printInfo(std::string const &message) const {
	using namespace std;

	cout << "\nINFO (";
	printProgramCounter(cout);
	cout << "): " << message << endl;
}

void VirtualMachine::printProgramCounter(std::ostream &stream) const {
	util::printHexNumberFormattedWithBase(stream << "pc=", programCounter-1);
}

void VirtualMachine::printState(std::ostream &stream) const {
	printProgramCounter(stream);
	util::printHexNumberFormattedWithBase(stream << "|ra=", registerFile.readReturnAddress());
	util::printHexNumberFormattedWithBase(stream << "|sp=", registerFile.readStackPointer());
	util::printHexNumberFormattedWithBase(stream << "|fp=", registerFile.readFramePointer());
	stream << "|z=" << zeroFlag << "|c=" << carryFlag << ": ";
}

void VirtualMachine::printInstructionOperandValues(std::ostream &stream, Mnemonic const mnemonic,
												   Register const ra, Register const rb) const {
	switch (util::numberOfRegisterOperands(mnemonic)) {
	case 0: break;
	case 1:
		printRegisterValue(stream << '(', ra)  << ')';
		break;
	case 2:
		printRegisterValue(stream << '(', ra);
		printRegisterValue(stream << '|', rb)  << ')';
		break;
	}
}

std::ostream& VirtualMachine::printRegisterValue(std::ostream &stream, Register const ra) const {
	stream << util::getCanonicalRegisterName(ra);
	util::printHexNumberFormattedWithBase(stream << '=', registerFile[ra]);

	return stream;
}

}	// namespace PROL16
