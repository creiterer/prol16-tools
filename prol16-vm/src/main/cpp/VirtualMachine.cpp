/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "VirtualMachine.h"

#include "NotImplementedError.h"
#include "OpcodeError.h"
#include "PrintUtils.h"
#include "Prol16ExeFile.h"
#include "StringUtils.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

using ::util::logging::Logger;

VirtualMachine::VirtualMachine(std::string const &filename, ::util::logging::Logger &logger,
							   bool const interactive, bool const shouldPrintDecimal)
: registerFile(VirtualMemory::StackStartAddress), carryFlag("carry flag"), zeroFlag("zero flag"),
  programCounter(registerFile.getProgramCounter()),
  logger(logger), commandInterpreter(nullptr), shouldPrintDecimal(shouldPrintDecimal) {
	util::Prol16ExeFile const p16ExeFile = util::Prol16ExeFile::parse(filename);

	symbolTable = p16ExeFile.getSymbolTable();
	logger << "symbol table (size=" << symbolTable.size() << ")\n";
	symbolTable.logTo(logger);

	// needs to be done before setting the program counter due to the
	// 'if (address >= memory.getCodeSegment()' check
	memory.initializeCodeSegment(p16ExeFile.getCodeSegment());

	VirtualMemory::Address const entryPointAddress = p16ExeFile.getEntryPointAddress();
	setProgramCounter(entryPointAddress);

	if (interactive) {
		setupCommandInterpreter();
	}

	logger << "starting execution of program '" << filename << "' at address ";
	logger.forEachLogStream([this, entryPointAddress](Logger::LogStream stream){
		::util::printHexNumberFormattedWithBase(stream, entryPointAddress);
		::util::printHexNumberFormattedWithBase(stream << " (css=", memory.getCodeSegmentSize());
		stream << ')';
	});
	logger << '\n';
}

void VirtualMachine::run() {
	bool stopProgramExecution = false;

	while ((programCounter < memory.getCodeSegmentSize()) && (!stopProgramExecution)) {
		if (commandInterpreter != nullptr) {
			commandInterpreter->run();
		}

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
		logger.setFormat(InstructionLogWidth, ' ', Logger::Adjustment::Left);
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
		::util::printHexNumberFormattedWithBase(instructionStream << ", ", immediate);

		logger.setFormat(InstructionLogWidth, ' ', Logger::Adjustment::Left);
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

	case JUMP: {
		Address const targetAddress = registerFile[ra];
		if (rtlib::isRuntimeLibFunctionAddress(targetAddress)) {
			executeRuntimeLibFunction(targetAddress);
		} else {
			setProgramCounter(targetAddress);
		}
		break;
	}

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
		::util::printHexNumberFormattedWithBase(errorMessage, programCounter) << ") ";
		errorMessage << "to an invalid address (";
		::util::printHexNumberFormattedWithBase(errorMessage, address) << ")";

		throw std::runtime_error(errorMessage.str());
	}

	programCounter = address;
}

void VirtualMachine::setZeroFlag(RegisterFile::Data const result) {
	zeroFlag.set(result == 0);
}

void VirtualMachine::setCarryFlag(ArithmeticResult const &result) {
	// if the 16th bit is set, there was an overflow/underflow -> set carry
	carryFlag.set(result.isOverflow(BitWidth));
}

void VirtualMachine::executeAdd(Register const ra, Register const rb, bool const withCarry) {
	ArithmeticResult result = 0;
	if (withCarry) {
		result = static_cast<ArithmeticResult::ResultType>(registerFile[ra]) + registerFile[rb] + (carryFlag ? 1 : 0);
	} else {
		result = static_cast<ArithmeticResult::ResultType>(registerFile[ra]) + registerFile[rb];
	}

	registerFile[ra] = static_cast<RegisterFile::Data>(result);
	setZeroFlag(registerFile[ra]);
	setCarryFlag(result);
}

void VirtualMachine::executeSub(Register const ra, Register const rb, bool const withCarry, bool const storeResult) {
	ArithmeticResult result = 0;
	if (withCarry) {
		result = static_cast<ArithmeticResult::ResultType>(registerFile[ra]) - registerFile[rb] - (carryFlag ? 1 : 0);
	} else {
		result = static_cast<ArithmeticResult::ResultType>(registerFile[ra]) - registerFile[rb];
	}

	if (storeResult) {
		registerFile[ra] = static_cast<RegisterFile::Data>(result);
	}

	setZeroFlag(static_cast<RegisterFile::Data>(result));
	setCarryFlag(result);
}

void VirtualMachine::executeInc(Register const ra) {
	ArithmeticResult result = 0;
	result = static_cast<ArithmeticResult::ResultType>(registerFile[ra]) + 1;

	registerFile[ra] = static_cast<RegisterFile::Data>(result);
	setZeroFlag(registerFile[ra]);
	setCarryFlag(result);
}

void VirtualMachine::executeDec(Register const ra) {
	ArithmeticResult result = 0;
	result = static_cast<ArithmeticResult::ResultType>(registerFile[ra]) - 1;

	registerFile[ra] = static_cast<RegisterFile::Data>(result);
	setZeroFlag(registerFile[ra]);
	setCarryFlag(result);
}

void VirtualMachine::executeShl(Register const ra, bool const withCarry) {
	// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
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
		// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
		registerFile[ra] |= 0x8000;	// shift in carry from the right -> set bit 15 to carry
	}

	setZeroFlag(registerFile[ra]);
}

void VirtualMachine::executeRuntimeLibFunction(Address const address) {
	using namespace PROL16::rtlib;

	logger << "\nexecuting runtime library function: ";

	switch (address) {
	case PRINT:
		if (!logger.isEnabled()) {
			printData(std::cout, registerFile[4]);
		}

		logger.forEachLogStream([this](auto &stream){
			stream << "_print r4 (";
			printRegisterValue(stream, 4) << ")\n";
			::util::printHexNumberFormattedWithBase(stream << '\n', registerFile[4]);
		});

		break;

	case PRINT32: {
		uint32_t const value = (static_cast<uint32_t>(registerFile[5]) << 16) + registerFile[4];
		if (!logger.isEnabled()) {
			printData(std::cout, value);
		}

		logger.forEachLogStream([this, value](auto &stream){
			stream << "_print32 r4, r5 (";
			printRegisterValue(stream, 4) << '|';
			printRegisterValue(stream, 5) << ")\n";
			::util::printHexNumberFormattedWithBase(stream << '\n', value);
		});

		break;
	}

	case PRINTSTR: {
		std::string const str = memory.readString(registerFile[4]);

		if (!logger.isEnabled()) {
			std::cout << str;
		}

		logger << "_printstr r4 (r4=" << ::util::formatAsHexNumberWithBase(registerFile[4]);
		logger << '=' << ::util::getQuoted(::util::getEscaped(str)) << ")\n";

		logger.forEachLogStream([str](::util::logging::Logger::LogStream stream){
			stream << '\n' << str;
		});

		break;
	}

	case MUL:
		logRuntimeLibCall(MUL);
		executeMul(std::make_pair(4, 6), std::make_pair(4, 5));
		break;
	case DIV:
		logRuntimeLibCall(DIV);
		// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
		registerFile[4] = registerFile[4] / registerFile[6];
		break;
	case DIVU:
		logRuntimeLibCall(DIVU);
		// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
		registerFile[4] = registerFile[4] / registerFile[6];
		break;
	case MOD:
		logRuntimeLibCall(MOD);
		// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
		registerFile[4] = registerFile[4] % registerFile[6];
		break;
	case MODU:
		logRuntimeLibCall(MODU);
		// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
		registerFile[4] = registerFile[4] % registerFile[6];
		break;
	default:
		throw std::runtime_error(::util::format("Invalid address (%#hx) for runtime library function call"));
	}
}

void VirtualMachine::executeMul(RegisterPair const &srcRegs,  RegisterPair const &destRegs) {
	ArithmeticResult const result = static_cast<ArithmeticResult::ResultType>(registerFile[srcRegs.first]) * registerFile[srcRegs.second];

	registerFile[destRegs.first] = result.getLow();
	registerFile[destRegs.second] = result.getHigh();
}

void VirtualMachine::printInfo(std::string const &message) const {
	using namespace std;

	cout << "\nINFO (";
	printProgramCounter(cout);
	cout << "): " << message << endl;
}

void VirtualMachine::printProgramCounter(std::ostream &stream) const {
	::util::printHexNumberFormattedWithBase(stream << "pc=", programCounter-1);
}

void VirtualMachine::printState(std::ostream &stream) const {
	printProgramCounter(stream);
	::util::printHexNumberFormattedWithBase(stream << "|ra=", registerFile.readReturnAddress());
	::util::printHexNumberFormattedWithBase(stream << "|sp=", registerFile.readStackPointer());
	::util::printHexNumberFormattedWithBase(stream << "|fp=", registerFile.readFramePointer());
	stream << "|z=" << zeroFlag << "|c=" << carryFlag << ": ";
}

void VirtualMachine::printInstructionOperandValues(std::ostream &stream, Mnemonic const mnemonic,
												   Register const ra, Register const rb) const {
	switch (util::numberOfRegisterOperands(mnemonic)) {
	case 0: break;
	case 1: {
		Data const registerValue = registerFile[ra];
		printRegisterValue(stream << '(', ra);
		if (isAnyJump(mnemonic) && symbolTable.contains(registerValue)) {
			stream << '=' << symbolTable.getSymbolName(registerValue);
		}
		stream << ')';
		break;
	}
	case 2:
		printRegisterValue(stream << '(', ra);
		printRegisterValue(stream << '|', rb)  << ')';
		break;
	}
}

std::ostream& VirtualMachine::printRegisterValue(std::ostream &stream, Register const ra) const {
	stream << util::getCanonicalRegisterName(ra);
	::util::printHexNumberFormattedWithBase(stream << '=', registerFile[ra]);

	return stream;
}

std::ostream& VirtualMachine::printMemoryValue(std::ostream &stream, Address const address) const {
	::util::printHexNumberFormatted(stream, address);
	::util::printHexNumberFormattedWithBase(stream << ": ", memory.read(address));

	return stream;
}

template <typename T>
std::ostream& VirtualMachine::printData(std::ostream &stream, T const data) const {
	if (shouldPrintDecimal) {
		stream << data;
	} else {
		::util::printHexNumberFormattedWithBase(stream, data);
	}

	return stream;
}

void VirtualMachine::logRuntimeLibCall(rtlib::RuntimeLibFunctionAddress const address) {
	logger << rtlib::getRuntimeLibFunctionName(address) <<  " r4, r6 (";
	logger << "r4=" << ::util::formatAsHexNumberWithBase(registerFile[4]) << '|';
	logger << "r6=" << ::util::formatAsHexNumberWithBase(registerFile[6]) << ")\n";
}

void VirtualMachine::setupCommandInterpreter() {
	commandInterpreter = std::make_unique<::util::CommandInterpreter>("> ");
	commandInterpreter->registerCommand("m", "memory", 1, 2, "ADDRESS | ADDRESS_RANGE -- print memory of the given address (range)",
										std::bind(&VirtualMachine::printMemoryCommand, this, std::placeholders::_1));
	commandInterpreter->registerCommand("r", "register", 1, 1, "REG_NUMBER -- print the given register",
										std::bind(&VirtualMachine::printRegisterCommand, this, std::placeholders::_1));
}

void VirtualMachine::printMemoryCommand(::util::CommandInterpreter::ArgumentVector const &arguments) const {
	if (arguments.size() == 1) {
		Address const address = stoul(arguments.at(0), nullptr, util::HexBase);
		printMemoryValue(std::cerr, address) << '\n';
	} else if (arguments.size() == 2) {
		Address const startAddress = stoul(arguments.at(0), nullptr, util::HexBase);
		Address const endAddress = stoul(arguments.at(1), nullptr, util::HexBase);

		for (uint32_t address = startAddress; address <= endAddress; ++address) {
			printMemoryValue(std::cerr, address) << '\n';
		}
	}
}

void VirtualMachine::printRegisterCommand(::util::CommandInterpreter::ArgumentVector const &arguments) const {
	if (arguments.size() == 1) {
		Register const reg = stoul(arguments.at(0));
		printRegisterValue(std::cerr, reg) << '\n';
	}
}

}	// namespace PROL16
