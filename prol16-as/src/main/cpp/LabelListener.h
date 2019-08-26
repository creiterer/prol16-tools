/**
 * @author		creiterer
 * @date 		2019-03-30
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_LABELLISTENER_H_INCLUDED
#define PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_LABELLISTENER_H_INCLUDED

#include "AddressUtils.h"
#include "CommandCounter.h"
#include "NumberUtils.h"
#include "Prol16AsmParserBaseListener.h"

#include <string>
#include <unordered_map>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class LabelListener final : public Prol16AsmParserBaseListener {
public:
	using LabelName = std::string;
	using LabelValue = util::Immediate;
	using LabelTable = std::unordered_map<LabelName, LabelValue>;

	LabelListener() = default;

	void enterLabelStatement(Prol16AsmParser::LabelStatementContext */*context*/) override;

	void enterNopInstruction(Prol16AsmParser::NopInstructionContext */*context*/) override;

	void enterSleepInstruction(Prol16AsmParser::SleepInstructionContext */*context*/) override;

	void enterLoadiInstruction(Prol16AsmParser::LoadiInstructionContext */*context*/) override;

	void enterLoadInstruction(Prol16AsmParser::LoadInstructionContext */*context*/) override;

	void enterStoreInstruction(Prol16AsmParser::StoreInstructionContext */*context*/) override;

	void enterMoveInstruction(Prol16AsmParser::MoveInstructionContext */*context*/) override;

	void enterJumpInstruction(Prol16AsmParser::JumpInstructionContext */*context*/) override;

	void enterJumpcInstruction(Prol16AsmParser::JumpcInstructionContext */*context*/) override;

	void enterJumpzInstruction(Prol16AsmParser::JumpzInstructionContext */*context*/) override;

	void enterAndInstruction(Prol16AsmParser::AndInstructionContext */*context*/) override;

	void enterOrInstruction(Prol16AsmParser::OrInstructionContext */*context*/) override;

	void enterXorInstruction(Prol16AsmParser::XorInstructionContext */*context*/) override;

	void enterNotInstruction(Prol16AsmParser::NotInstructionContext */*context*/) override;

	void enterAddInstruction(Prol16AsmParser::AddInstructionContext */*context*/) override;

	void enterAddcInstruction(Prol16AsmParser::AddcInstructionContext */*context*/) override;

	void enterSubInstruction(Prol16AsmParser::SubInstructionContext */*context*/) override;

	void enterSubcInstruction(Prol16AsmParser::SubcInstructionContext */*context*/) override;

	void enterCompInstruction(Prol16AsmParser::CompInstructionContext */*context*/) override;

	void enterIncInstruction(Prol16AsmParser::IncInstructionContext */*context*/) override;

	void enterDecInstruction(Prol16AsmParser::DecInstructionContext */*context*/) override;

	void enterShlInstruction(Prol16AsmParser::ShlInstructionContext */*context*/) override;

	void enterShrInstruction(Prol16AsmParser::ShrInstructionContext */*context*/) override;

	void enterShlcInstruction(Prol16AsmParser::ShlcInstructionContext */*context*/) override;

	void enterShrcInstruction(Prol16AsmParser::ShrcInstructionContext */*context*/) override;

	void enterPrintInstruction(Prol16AsmParser::PrintInstructionContext *context) override;

	inline LabelTable getLabels() const { return labelTable; }

	util::Address getLabelAddress(std::string const &labelName) const;

private:
	CommandCounter commandCounter;
	LabelTable labelTable;
};

}	// namespace PROL16

#endif /* PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_LABELLISTENER_H_INCLUDED */
