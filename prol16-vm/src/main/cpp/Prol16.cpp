#include "Prol16.h"

#include <cassert>

namespace Prol16 {

	TOpcode MaskOpcode(TInstruction const instruction) {
		TInstruction const mask1 = (TInstruction)(((TInstruction)~0) << cPosOpcode);
		TInstruction shiftedResult = mask1 & instruction;
		TInstruction result = shiftedResult >> cPosOpcode;
		return static_cast<TOpcode>(result);
	}

	size_t MaskRegRa(TInstruction const instruction) {
		TInstruction mask1 = (TInstruction)(((TInstruction)~0) << (cSizeInstruction - (cPosOpcode - cPosRegRa)));
		TInstruction mask2 = mask1 >> (cSizeInstruction - cPosOpcode);
		TInstruction result = (instruction & mask2) >> cPosRegRa;
		return result;
	}

	size_t MaskRegRb(TInstruction const instruction) {
		TInstruction mask1 = (TInstruction)(((TInstruction)~0) << (cSizeInstruction - (cPosRegRa - cPosRegRb)));
		TInstruction mask2 = mask1 >> (cSizeInstruction - cPosRegRa);
		TInstruction result = (mask2 & instruction) >> cPosRegRb;
		return result;
	}

	TInstruction GenInsturction(TOpcode const opcode, size_t const raIdx, size_t const rbIdx) {
		assert(raIdx < cRegCount);
		assert(rbIdx < cRegCount);
		return static_cast<TInstruction>(opcode) << cPosOpcode | raIdx << cPosRegRa | rbIdx << cPosRegRb;
	}

}
