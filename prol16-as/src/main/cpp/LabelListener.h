/**
 * @author		creiterer
 * @date 		2019-03-30
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Listener collecting all labels and their addresses.
 */

#ifndef PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_LABELLISTENER_H_INCLUDED
#define PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_LABELLISTENER_H_INCLUDED

#include "CommandCounter.h"
#include "LabelUtils.h"
#include "MemoryUtils.h"
#include "NumberUtils.h"
#include "Prol16AsmParserBaseListener.h"

#include <string>
#include <unordered_map>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class LabelListener final : public Prol16AsmParserBaseListener {
public:
	using LabelName = util::LabelName;
	using LabelValue = util::LabelValue;
	using LabelTable = util::LabelTable;

	using Address = PROL16::util::memory::Address;

	LabelListener();

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

	void enterDataWordStore(Prol16AsmParser::DataWordStoreContext *context) override;

	inline LabelTable getLabels() const { return labelTable; }

	Address getLabelAddress(std::string const &labelName) const;

	void addLabel(std::string const &labelName, int const offset = 0);

	inline Address getNextInstructionAddress() const { return commandCounter.getNextInstructionAddress(); }

	inline bool containsLabel(std::string const &labelName) const { return labelTable.count(labelName) != 0; }

private:
	CommandCounter commandCounter;
	LabelTable labelTable;
};

}	// namespace PROL16

#endif /* PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_LABELLISTENER_H_INCLUDED */
