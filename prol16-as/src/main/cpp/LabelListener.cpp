/**
 * @author		creiterer
 * @date 		2019-03-30
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Listener collecting all labels and their addresses.
 */

#include "LabelListener.h"

#include "ContextUtils.h"
#include "NotImplementedError.h"
#include "RuntimeLibrary.h"
#include "StringUtils.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

LabelListener::LabelListener() : labelTable(rtlib::RuntimeLibFunctions) {

}

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

void LabelListener::enterDataWordStore(Prol16AsmParser::DataWordStoreContext *context) {
	if (util::isImmediate(context)) {
		++commandCounter;
	} else if (util::isString(context)) {
		std::string const str = ::util::getUnquoted(::util::handleEscapeSequences(context->string->getText()));
		commandCounter += util::memory::calcStringSpaceInMemory(str);
	} else {
		std::ostringstream errorMessage;
		errorMessage << "argument of 'db', which is '" << context->getText() << "', is neither a number nor a string";

		throw std::runtime_error(errorMessage.str());
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
