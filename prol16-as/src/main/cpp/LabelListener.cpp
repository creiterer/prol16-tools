/**
 * @author		creiterer
 * @date 		2019-03-30
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "LabelListener.h"

#include "ContextUtils.h"
#include "NotImplementedError.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

void LabelListener::enterLabelStatement(Prol16AsmParser::LabelStatementContext *context) {
	addLabel(context->identifier->getText());
}

void LabelListener::enterNopInstruction(Prol16AsmParser::NopInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterSleepInstruction(Prol16AsmParser::SleepInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterLoadiInstruction(Prol16AsmParser::LoadiInstructionContext */*context*/) {
	commandCounter += 2;	// 'loadi' takes the space of two instructions: the instruction itself and the immediate
}

void LabelListener::enterLoadInstruction(Prol16AsmParser::LoadInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterStoreInstruction(Prol16AsmParser::StoreInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterMoveInstruction(Prol16AsmParser::MoveInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterJumpInstruction(Prol16AsmParser::JumpInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterJumpcInstruction(Prol16AsmParser::JumpcInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterJumpzInstruction(Prol16AsmParser::JumpzInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterAndInstruction(Prol16AsmParser::AndInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterOrInstruction(Prol16AsmParser::OrInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterXorInstruction(Prol16AsmParser::XorInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterNotInstruction(Prol16AsmParser::NotInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterAddInstruction(Prol16AsmParser::AddInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterAddcInstruction(Prol16AsmParser::AddcInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterSubInstruction(Prol16AsmParser::SubInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterSubcInstruction(Prol16AsmParser::SubcInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterCompInstruction(Prol16AsmParser::CompInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterIncInstruction(Prol16AsmParser::IncInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterDecInstruction(Prol16AsmParser::DecInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterShlInstruction(Prol16AsmParser::ShlInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterShrInstruction(Prol16AsmParser::ShrInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterShlcInstruction(Prol16AsmParser::ShlcInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterShrcInstruction(Prol16AsmParser::ShrcInstructionContext */*context*/) {
	++commandCounter;
}

void LabelListener::enterPrintInstruction(Prol16AsmParser::PrintInstructionContext *context) {
	if (util::isRegister(context)) {			// PRINT
		++commandCounter;		// 'print' needs only one instruction
	} else if (util::isImmediate(context)) {	// PRINTI
		commandCounter += 2;	// 'printi' takes the space of two instructions: the instruction itself and the immediate
	} else if (util::isString(context)) {
		throw ::util::NotImplementedError("print \"str\"");
	} else {
		throw std::runtime_error("invalid 'print' instruction; don't know how much the command counter needs to be incremented");
	}
}

LabelListener::Address LabelListener::getLabelAddress(std::string const &labelName) const {
	return labelTable.at(labelName);
}

void LabelListener::addLabel(std::string const &labelName, int const offset) {
	auto result = labelTable.emplace(labelName, commandCounter.getNextInstructionAddress() + offset);
	if (!result.second) {
		// TODO(creiterer): print error that the label is already defined (multiple definition)
	}
}

} 	// namespace PROL16
