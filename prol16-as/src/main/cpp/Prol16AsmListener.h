/**
 * @author		creiterer
 * @date 		2019-03-12
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Listener collecting all the assembly instructions.
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_PROL16ASMLISTENER_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_PROL16ASMLISTENER_H_INCLUDED

#include "InstructionWriter.h"
#include "LabelListener.h"
#include "NumberUtils.h"
#include "Prol16AsmParserBaseListener.h"

#include <cstdint>
#include <string>
#include <unordered_map>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class Prol16AsmListener final : public Prol16AsmParserBaseListener {
public:
	using LabelTable = LabelListener::LabelTable;

	Prol16AsmListener(util::InstructionWriter &instructionWriter, LabelTable labelTable);

	void enterNopInstruction(Prol16AsmParser::NopInstructionContext */*context*/) override;

	void enterSleepInstruction(Prol16AsmParser::SleepInstructionContext */*context*/) override;

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

	void enterCommandCounterLoad(Prol16AsmParser::CommandCounterLoadContext */*context*/) override;

	void enterDataWordStore(Prol16AsmParser::DataWordStoreContext *context) override;

	void enterSymbolicConstantDefinition(Prol16AsmParser::SymbolicConstantDefinitionContext *context) override;

	void enterMacroDefinition(Prol16AsmParser::MacroDefinitionContext */*context*/) override;

	void enterMacroCall(Prol16AsmParser::MacroCallContext */*context*/) override;

	void enterTextSectionStart(Prol16AsmParser::TextSectionStartContext */*context*/) override;

	void enterDataSectionStart(Prol16AsmParser::DataSectionStartContext */*context*/) override;

private:
	using SymbolName = std::string;
	using SymbolValue = util::Immediate;
	using SymbolicConstantTable = std::unordered_map<SymbolName, SymbolValue>;

	util::InstructionWriter &instructionWriter;
	SymbolicConstantTable symbolicConstantTable;
	LabelTable const labelTable;

	util::InstructionWriter::Immediate evaluateExpression(Prol16AsmParser::ExpressionContext * const expression) const;
};

}	// namespace PROL16

#endif /* PROL16_AS_SRC_MAIN_CPP_PROL16ASMLISTENER_H_INCLUDED */
