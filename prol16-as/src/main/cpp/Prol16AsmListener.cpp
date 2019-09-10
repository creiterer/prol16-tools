/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Prol16AsmListener.h"

#include "ContextUtils.h"
#include "NotImplementedError.h"
#include "RegisterUtils.h"
#include "StringUtils.h"

#include <sstream>
#include <stdexcept>
#include <utility>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

using util::InstructionWriter;

Prol16AsmListener::Prol16AsmListener(util::InstructionWriter &instructionWriter, LabelTable labelTable)
: instructionWriter(instructionWriter), labelTable(std::move(labelTable)) {

}

void Prol16AsmListener::enterNopInstruction(Prol16AsmParser::NopInstructionContext */*context*/) {
	instructionWriter.writeNop();
}

void Prol16AsmListener::enterSleepInstruction(Prol16AsmParser::SleepInstructionContext */*context*/) {
	instructionWriter.writeSleep();
}

void Prol16AsmListener::enterLoadiInstruction(Prol16AsmParser::LoadiInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Immediate const immediate = evaluateExpression(context->immediate);
	instructionWriter.writeLoadi(ra, immediate);
}

void Prol16AsmListener::enterLoadInstruction(Prol16AsmParser::LoadInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeLoad(ra, rb);
}

void Prol16AsmListener::enterStoreInstruction(Prol16AsmParser::StoreInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeStore(ra, rb);
}

void Prol16AsmListener::enterMoveInstruction(Prol16AsmParser::MoveInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeMove(ra, rb);
}

void Prol16AsmListener::enterJumpInstruction(Prol16AsmParser::JumpInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeJump(ra);
}

void Prol16AsmListener::enterJumpcInstruction(Prol16AsmParser::JumpcInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeJumpc(ra);
}

void Prol16AsmListener::enterJumpzInstruction(Prol16AsmParser::JumpzInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeJumpz(ra);
}

void Prol16AsmListener::enterAndInstruction(Prol16AsmParser::AndInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeAnd(ra, rb);
}

void Prol16AsmListener::enterOrInstruction(Prol16AsmParser::OrInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeOr(ra, rb);
}

void Prol16AsmListener::enterXorInstruction(Prol16AsmParser::XorInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeXor(ra, rb);
}

void Prol16AsmListener::enterNotInstruction(Prol16AsmParser::NotInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeNot(ra);
}

void Prol16AsmListener::enterAddInstruction(Prol16AsmParser::AddInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeAdd(ra, rb);
}

void Prol16AsmListener::enterAddcInstruction(Prol16AsmParser::AddcInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeAddc(ra, rb);
}

void Prol16AsmListener::enterSubInstruction(Prol16AsmParser::SubInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeSub(ra, rb);
}

void Prol16AsmListener::enterSubcInstruction(Prol16AsmParser::SubcInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeSubc(ra, rb);
}

void Prol16AsmListener::enterCompInstruction(Prol16AsmParser::CompInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
	InstructionWriter::Register const rb = util::parseRegisterNumberChecked(context->rb->getText());

	instructionWriter.writeComp(ra, rb);
}

void Prol16AsmListener::enterIncInstruction(Prol16AsmParser::IncInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeInc(ra);
}

void Prol16AsmListener::enterDecInstruction(Prol16AsmParser::DecInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeDec(ra);
}

void Prol16AsmListener::enterShlInstruction(Prol16AsmParser::ShlInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeShl(ra);
}

void Prol16AsmListener::enterShrInstruction(Prol16AsmParser::ShrInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeShr(ra);
}

void Prol16AsmListener::enterShlcInstruction(Prol16AsmParser::ShlcInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeShlc(ra);
}

void Prol16AsmListener::enterShrcInstruction(Prol16AsmParser::ShrcInstructionContext *context) {
	InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());

	instructionWriter.writeShrc(ra);
}

void Prol16AsmListener::enterCommandCounterLoad(Prol16AsmParser::CommandCounterLoadContext */*context*/) {
	throw ::util::NotImplementedError("'org' directive");
}

void Prol16AsmListener::enterDataWordStore(Prol16AsmParser::DataWordStoreContext *context) {
	if (util::isNumber(context)) {
		instructionWriter.writeImmediate(util::parseNumber(context->number->getText()));
	} else if (util::isString(context)) {
		instructionWriter.writeString(::util::getUnquoted(::util::handleEscapeSequences(context->string->getText())));
	} else {
		std::ostringstream errorMessage;
		errorMessage << "argument of 'db', which is '" << context->getText() << "', is neither a number nor a string";

		throw std::runtime_error(errorMessage.str());
	}
}

void Prol16AsmListener::enterSymbolicConstantDefinition(Prol16AsmParser::SymbolicConstantDefinitionContext *context) {
	SymbolValue const value = util::parseNumber(context->number->getText());

	auto result = symbolicConstantTable.emplace(context->identifier->getText(), value);
	if (!result.second) {
		// TODO(creiterer): print error that the symbolic constant is already defined (multiple definition)
	}
}

void Prol16AsmListener::enterMacroDefinition(Prol16AsmParser::MacroDefinitionContext */*context*/) {
	throw ::util::NotImplementedError("macro definition");
}

void Prol16AsmListener::enterMacroCall(Prol16AsmParser::MacroCallContext */*context*/) {
	throw ::util::NotImplementedError("macro call");
}

void Prol16AsmListener::enterPrintInstruction(Prol16AsmParser::PrintInstructionContext *context) {
	if (util::isRegister(context)) {			// PRINT
		InstructionWriter::Register const ra = util::parseRegisterNumberChecked(context->ra->getText());
		instructionWriter.writePrint(ra);
	} else if (util::isImmediate(context)) {	// PRINTI
		instructionWriter.writePrinti(evaluateExpression(context->immediate));
	} else if (util::isString(context)) {
//		instructionWriter.writePrint(context->string->getText());
		throw ::util::NotImplementedError("print \"str\"");
	} else {
		std::ostringstream errorMessage;
		errorMessage << "argument of 'print', which is '" << context->getText() << "', is neither a register nor an immediate nor a string";

		throw std::runtime_error(errorMessage.str());
	}
}

util::InstructionWriter::Immediate Prol16AsmListener::evaluateExpression(Prol16AsmParser::ExpressionContext * const expression) const {
	if (util::isNumber(expression)) {
		return util::parseNumber(expression->number->getText());
	}

	if (util::isIdentifier(expression)) {
		std::string const identifier = expression->identifier->getText();
		try {
			return symbolicConstantTable.at(identifier);
		} catch (std::out_of_range const&) {
			try {
				return labelTable.at(identifier);
			} catch (std::out_of_range const&) {
				std::ostringstream errorMessage;
				errorMessage << "identifier '" << identifier << "' is not defined";

				throw std::runtime_error(errorMessage.str());
			}
		}
	}

	std::ostringstream errorMessage;
	errorMessage << "expression '" << expression->getText() << "' is neither a number nor an identifier";

	throw std::runtime_error(errorMessage.str());
}

} 	// namespace PROL16
