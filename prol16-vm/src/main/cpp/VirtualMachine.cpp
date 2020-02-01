/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class emulating a PROL16 target machine.
 */

#include "VirtualMachine.h"

#include "NotImplementedError.h"
#include "OpcodeError.h"
#include "PrintUtils.h"
#include "Prol16ExeFile.h"
#include "StringUtils.h"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

using ::util::logging::Logger;

VirtualMachine::VirtualMachine(std::string const &filename, ::util::logging::Logger &logger,
							   bool const interactive, bool const shouldPrintDecimal,
							   ::util::Flavor const flavor)
: registerFile(VirtualMemory::StackStartAddress), carryFlag("carry flag"), zeroFlag("zero flag"),
  programCounter(registerFile.getProgramCounter()),
  logger(logger), commandInterpreter(nullptr),
  shouldPrintDecimal(shouldPrintDecimal), flavor(flavor) {
	if (flavor == ::util::Flavor::Unknown) {
		throw std::runtime_error("unknown flavor");
	}

	util::Prol16ExeFile const p16ExeFile = util::Prol16ExeFile::parse(filename);

	symbolTable = p16ExeFile.getSymbolTable();
	logger << "symbol table (size=" << symbolTable.size() << ")\n";
	symbolTable.logTo(logger);

	// needs to be done before setting the program counter due to the
	// 'if (address >= memory.getCodeSegment()' check
	memory.initializeCodeSegment(p16ExeFile.getCodeSegment());

	entryPointAddress = p16ExeFile.getEntryPointAddress();
	initFuncAddress = p16ExeFile.getInitFuncAddress();

	if (interactive) {
		setupCommandInterpreter();
	}

	logger << "executing program '" << filename << "' (css=";
	logger << ::util::formatAsHexNumberWithBase(memory.getCodeSegmentSize()) << ")\n";
}

void VirtualMachine::run() {
	if (memory.isCodeAddressValid(initFuncAddress)) {
		run(initFuncAddress, "init func");
	}

	run(entryPointAddress, "entry point");
}

void VirtualMachine::run(Address const startAddress, std::string const &description) {
	logger << "starting execution of " << description << " at address ";
	logger << ::util::formatAsHexNumberWithBase(startAddress) << '\n';

	setProgramCounter(startAddress);

	bool stopProgramExecution = false;

	while ((programCounter < memory.getCodeSegmentSize()) && (!stopProgramExecution)) {
		Instruction instruction = fetchAndDecodeInstruction();

		if (commandInterpreter != nullptr && !commandInterpreter->isQuit()) {
			printInstruction(std::cerr, instruction);
			commandInterpreter->run();
		}

		stopProgramExecution = executeInstruction(instruction);
	}
}

VirtualMachine::Instruction VirtualMachine::fetchAndDecodeInstruction() {
	return Instruction::decode(memory[programCounter++]);
}

VirtualMachine::Immediate VirtualMachine::fetchImmediate() {
	return memory[programCounter++];
}

VirtualMachine::Immediate VirtualMachine::prefetchImmediate() const {
	return memory[programCounter];
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
		logger << "stopping execution: reached 'sleep' instruction\n";
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
	if (!memory.isCodeAddressValid(address)) {
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
	bool const newCarryValue = (registerFile[ra] & 0x8000) != 0;
	registerFile[ra] <<= 1;

	if (withCarry && carryFlag.isSet()) {
		registerFile[ra] |= 0x0001;	// shift in carry from the left -> set bit 0 to carry
	}

	setZeroFlag(registerFile[ra]);
	carryFlag.set(newCarryValue);
}

void VirtualMachine::executeShr(Register const ra, bool const withCarry) {
	bool const newCarryValue = (registerFile[ra] & 0x0001) != 0;
	registerFile[ra] >>= 1;

	if (withCarry && carryFlag.isSet()) {
		// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
		registerFile[ra] |= 0x8000;	// shift in carry from the right -> set bit 15 to carry
	}

	setZeroFlag(registerFile[ra]);
	carryFlag.set(newCarryValue);
}

void VirtualMachine::executeRuntimeLibFunction(Address const address) {
	using namespace PROL16::rtlib;

	logger << "\nexecuting runtime library function (flavor=" << ::util::getFlavorAsString(flavor) << "): ";

	switch (address) {
	case PRINT_UINT16: {
		Register const reg = isGoFlavor() ? 5 : 4;

		if (!logger.isEnabled()) {
			printData(std::cout, registerFile[reg]);
		}

		logRuntimeLibCall(address, reg);
		logger << '\n' << ::util::formatAsHexNumberWithBase(registerFile[reg]);

		break;
	}

	case PRINT_UINT32: {
		Register const lowReg = isGoFlavor() ? 5 : 4;
		Register const highReg = isGoFlavor() ? 6 : 5;
		uint32_t const value = (static_cast<uint32_t>(registerFile[highReg]) << 16) + registerFile[lowReg];

		if (!logger.isEnabled()) {
			printData(std::cout, value);
		}

		logRuntimeLibCall(address, lowReg, highReg);
		logger << '\n' << ::util::formatAsHexNumberWithBase(value);

		break;
	}

	case PRINT_RUNE: {
		Register const lowReg = isGoFlavor() ? 5 : 4;
		Register const highReg = isGoFlavor() ? 6 : 5;

		if (registerFile[highReg] != 0 || registerFile[lowReg] > std::numeric_limits<char>::max()) {
			throw ::util::NotImplementedError(::util::format("UTF-8 encoded runes (%#hx %#hx)", registerFile[highReg], registerFile[lowReg]));
		}

		auto const rune = static_cast<char>(registerFile[lowReg]);

		if (!logger.isEnabled()) {
			std::cout << rune;
		}

		logger << getRuntimeLibFunctionName(PRINT_RUNE) << ' ';
		logRegisterNames(lowReg, highReg);
		logger << " (" << PROL16::util::getCanonicalRegisterName(lowReg) << '=' << ::util::formatAsHexNumberWithBase(registerFile[lowReg]);
		logger << '=' << ::util::getQuoted(rune);
		logger << '|' << PROL16::util::getCanonicalRegisterName(highReg) << '=' << ::util::formatAsHexNumberWithBase(registerFile[highReg]);
		logger << ")\n\n" << rune;

		break;
	}

	case PRINT_STRING: {
		Register const reg = isGoFlavor() ? 5 : 4;
		std::string const str = memory.readString(registerFile[reg]);

		if (!logger.isEnabled()) {
			std::cout << str;
		}

		logger << getRuntimeLibFunctionName(PRINT_STRING) << ' ' << PROL16::util::getCanonicalRegisterName(reg);
		logger << " (" << PROL16::util::getCanonicalRegisterName(reg) << '=' << ::util::formatAsHexNumberWithBase(registerFile[reg]);
		logger << '=' << ::util::getQuoted(::util::getEscaped(str));

		if (isGoFlavor()) {
			logger << '|' << PROL16::util::getCanonicalRegisterName(6) << '=' << registerFile[6];
		}

		logger << ")\n\n" << str;

		break;
	}

	case PRINT_POINTER: {
		Register const reg = isGoFlavor() ? 5 : 4;

		if (!logger.isEnabled()) {
			printData(std::cout, registerFile[reg]);
		}

		logRuntimeLibCall(address, reg);
		logger << '\n' << ::util::formatAsHexNumberWithBase(registerFile[reg]);

		break;
	}

	case PRINT_NL:
		if (!logger.isEnabled()) {
			std::cout << '\n';
		}

		logger << getRuntimeLibFunctionName(PRINT_NL) << '\n' << '\n';

		break;

	case PRINT_SPACE:
		if (!logger.isEnabled()) {
			std::cout << ' ';
		}

		logger << getRuntimeLibFunctionName(PRINT_SPACE) << '\n' << ' ';

		break;

	case MUL_I16: {
		constexpr Register ra = 4;
		constexpr Register rb = 5;

		logRuntimeLibCall(MUL_I16, ra, rb);
		registerFile[ra] = registerFile[ra] * registerFile[rb];
		break;
	}
	case MUL_I32: {
		constexpr Register raLow = 4;
		constexpr Register raHigh = 5;
		constexpr Register rbLow = 6;
		constexpr Register rbHigh = 7;

		logRuntimeLibCall(MUL_I32, raLow, rbLow);
		executeMul32(std::make_pair(raLow, raHigh), std::make_pair(rbLow, rbHigh), std::make_pair(4, 5));
		break;
	}
	case SDIV_I16:
	case UDIV_I16:
	case SDIV_I32:
	case UDIV_I32: {
		constexpr Register ra = 4;
		Register const rb = isDiv32(address) ? 6 : 5;

		logRuntimeLibCall(address, ra, rb);

		// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
		registerFile[4] = registerFile[ra] / registerFile[rb];
		break;
	}
	case SREM_I16:
	case UREM_I16:
	case SREM_I32:
	case UREM_I32: {
		constexpr Register ra = 4;
		Register const rb = isRem32(address) ? 6 : 5;

		logRuntimeLibCall(address, ra, rb);

		// NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
		registerFile[4] = registerFile[ra] % registerFile[rb];

		break;
	}
	case MEMCPY: {
		constexpr Register destinationReg = 4;
		constexpr Register sourceReg = 5;
		constexpr Register numBytesReg = 6;

		logRuntimeLibCall(address, destinationReg, sourceReg, numBytesReg);

		memory.memcpy(registerFile[destinationReg], registerFile[sourceReg], registerFile[numBytesReg]);

		break;
	}
	case MEMSET: {
		constexpr Register destinationReg = 4;
		constexpr Register valueReg = 5;
		constexpr Register numBytesReg = 6;

		logRuntimeLibCall(address, destinationReg, valueReg, numBytesReg);

		memory.memset(registerFile[destinationReg], registerFile[valueReg], registerFile[numBytesReg]);

		break;
	}
	case SBRK: {
		constexpr Register reg = 4;

		logRuntimeLibCall(address, reg);

		registerFile[reg] = memory.incrementHeapBreak(registerFile[reg]);

		break;
	}
	default:
		throw std::runtime_error(::util::format("Invalid address (%#hx) for runtime library function call", address));
	}
}

void VirtualMachine::executeMul32(RegisterPair const &ra, RegisterPair const &rb, RegisterPair const &destRegs) {
	if (registerFile[ra.second] != 0 || registerFile[rb.second] != 0) {
		throw ::util::NotImplementedError("32-bit multiplication");
	}

	ArithmeticResult const result = static_cast<ArithmeticResult::ResultType>(registerFile[ra.first]) * registerFile[rb.first];

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
	::util::printHexNumberFormattedWithBase<Address>(stream << "pc=", programCounter-1);
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
		printRegisterValue(stream << '|', rb);
		if (mnemonic == util::LOAD) {
			stream << "->" << memory[registerFile[rb]];
		}
		stream << ')';
		break;
	}
}

void VirtualMachine::printInstruction(std::ostream &stream, Instruction const &instruction) const {
	Mnemonic const mnemonic = instruction.getMnemonic();
	Register const ra = instruction.getRa();
	Register const rb = instruction.getRb();

	printState(stream);

	std::ostringstream instructionStream;
	instructionStream << instruction;

	if (mnemonic == util::LOADI) {
		Immediate const immediate = prefetchImmediate();
		::util::printHexNumberFormattedWithBase(instructionStream << ", ", immediate);
	}

	stream << std::setfill(' ') << std::setw(InstructionLogWidth) << std::left << instructionStream.str();
	stream << std::resetiosflags(std::ios::adjustfield);
	printInstructionOperandValues(stream, mnemonic, ra, rb);

	stream << '\n';
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

template <typename... Registers>
void VirtualMachine::logRegisterNames(Register const reg, Registers const... registers) const {
	logger << PROL16::util::getCanonicalRegisterName(reg) << ", ";
	logRegisterNames(registers...);
}

void VirtualMachine::logRegisterNames(Register const reg) const {
	logger << PROL16::util::getCanonicalRegisterName(reg);
}

template <typename... Registers>
void VirtualMachine::logRegisterValues(Register const reg, Registers const... registers) const {
	logger << PROL16::util::getCanonicalRegisterName(reg) << '=' << ::util::formatAsHexNumberWithBase(registerFile[reg]) << '|';
	logRegisterValues(registers...);
}

void VirtualMachine::logRegisterValues(Register const reg) const {
	logger << PROL16::util::getCanonicalRegisterName(reg) << '=' << ::util::formatAsHexNumberWithBase(registerFile[reg]);
}

template <typename... Registers>
void VirtualMachine::logRuntimeLibCall(PROL16::util::memory::Address const address, Registers const... registers) const {
	logger << rtlib::getRuntimeLibFunctionName(address) << ' ';
	logRegisterNames(registers...);
	logger << " (";
	logRegisterValues(registers...);
	logger << ")\n";
}

void VirtualMachine::setupCommandInterpreter() {
	commandInterpreter = std::make_unique<::util::CommandInterpreter>("> ");
	commandInterpreter->registerCommand("m", "memory", 1, 2, "ADDRESS | ADDRESS_RANGE -- print memory of the given address (range)",
										std::bind(&VirtualMachine::printMemoryCommand, this, std::placeholders::_1));
	commandInterpreter->registerCommand("r", "register", 1, 1, "REG_NUMBER -- print the given register",
										std::bind(&VirtualMachine::printRegisterCommand, this, std::placeholders::_1));
	commandInterpreter->registerCommand("s", "stack", 0, 0, "-- show the current stack",
										[this](auto const &/*arguments*/){
		size_t const stackStartAddress = VirtualMemory::StackStartAddress;
		size_t const stackEndAddress = registerFile.readStackPointer();

		for (size_t address = stackStartAddress; address >= stackEndAddress; --address) {
			printMemoryValue(std::cerr, address) << '\n';
		}
	});
	commandInterpreter->registerCommand("f", "frame", 0, 0, "-- show the current stack frame",
										[this](auto const &/*arguments*/){
		uint32_t const frameStartAddress = registerFile.readFramePointer();
		uint32_t const frameEndAddress = registerFile.readStackPointer();

		for (uint32_t address = frameStartAddress; address >= frameEndAddress; --address) {
			printMemoryValue(std::cerr, address) << '\n';
		}
	});
	commandInterpreter->registerContinueCommand("n", "next",
												"[CONTINUE_COUNT] -- execute the next (CONTINUE_COUNT, default 1) instruction(s)");
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
