/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_PROL16ASMLISTENER_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_PROL16ASMLISTENER_H_INCLUDED

#include <unordered_map>
#include <string>
#include <cstdint>

#include "Prol16AsmParserBaseListener.h"
#include "InstructionWriter.h"
#include "NumberUtils.h"
#include "LabelListener.h"

namespace PROL16 {

class Prol16AsmListener final : public Prol16AsmParserBaseListener {
public:
	using LabelTable = LabelListener::LabelTable;

	Prol16AsmListener(InstructionWriter &instructionWriter, LabelTable const &labelTable);
	~Prol16AsmListener() = default;

	void enterNopInstruction(Prol16AsmParser::NopInstructionContext *context) override;

	void enterSleepInstruction(Prol16AsmParser::SleepInstructionContext *context) override;

	void enterLoadiInstruction(Prol16AsmParser::LoadiInstructionContext *context) override;

	void enterLoadInstruction(Prol16AsmParser::LoadInstructionContext *context) override;

	void enterStoreInstruction(Prol16AsmParser::StoreInstructionContext *context) override;

	void enterMoveInstruction(Prol16AsmParser::MoveInstructionContext *context) override;

	void enterJumpInstruction(Prol16AsmParser::JumpInstructionContext *context) override;

	void enterJumpcInstruction(Prol16AsmParser::JumpcInstructionContext *context) override;

	void enterJumpzInstruction(Prol16AsmParser::JumpzInstructionContext *context) override;

	void enterAndInstruction(Prol16AsmParser::AndInstructionContext *context) override;

	void enterOrInstruction(Prol16AsmParser::OrInstructionContext *context) override;

	void enterXorInstruction(Prol16AsmParser::XorInstructionContext *context) override;

	void enterNotInstruction(Prol16AsmParser::NotInstructionContext *context) override;

	void enterAddInstruction(Prol16AsmParser::AddInstructionContext *context) override;

	void enterAddcInstruction(Prol16AsmParser::AddcInstructionContext *context) override;

	void enterSubInstruction(Prol16AsmParser::SubInstructionContext *context) override;

	void enterSubcInstruction(Prol16AsmParser::SubcInstructionContext *context) override;

	void enterCompInstruction(Prol16AsmParser::CompInstructionContext *context) override;

	void enterIncInstruction(Prol16AsmParser::IncInstructionContext *context) override;

	void enterDecInstruction(Prol16AsmParser::DecInstructionContext *context) override;

	void enterShlInstruction(Prol16AsmParser::ShlInstructionContext *context) override;

	void enterShrInstruction(Prol16AsmParser::ShrInstructionContext *context) override;

	void enterShlcInstruction(Prol16AsmParser::ShlcInstructionContext *context) override;

	void enterShrcInstruction(Prol16AsmParser::ShrcInstructionContext *context) override;

	void enterCommandCounterLoad(Prol16AsmParser::CommandCounterLoadContext *context) override;

	void enterDataWordStore(Prol16AsmParser::DataWordStoreContext *context) override;

	void enterSymbolicConstantDefinition(Prol16AsmParser::SymbolicConstantDefinitionContext *context) override;

	void enterMacroDefinition(Prol16AsmParser::MacroDefinitionContext *context) override;

	void enterMacroCall(Prol16AsmParser::MacroCallContext *context) override;

private:
	using SymbolName = std::string;
	using SymbolValue = util::Immediate;
	using SymbolicConstantTable = std::unordered_map<SymbolName, SymbolValue>;

	InstructionWriter &instructionWriter;
	SymbolicConstantTable symbolicConstantTable;
	LabelTable const labelTable;

	InstructionWriter::Immediate evaluateExpression(Prol16AsmParser::ExpressionContext * const expression) const;
	bool isNumber(Prol16AsmParser::ExpressionContext const * const expression) const;
	bool isIdentifier(Prol16AsmParser::ExpressionContext const * const expression) const;
};

}

#endif /* PROL16_AS_SRC_MAIN_CPP_PROL16ASMLISTENER_H_INCLUDED */
