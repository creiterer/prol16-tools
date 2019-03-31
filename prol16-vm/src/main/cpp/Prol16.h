#ifndef PROL16_H
#define PROL16_H

#include <cstddef>
#include <cstdint>

namespace Prol16 {

	typedef uint16_t TInstruction;
	typedef uint16_t TAddress;
	typedef uint16_t TData;
	typedef uint8_t TByte;

	size_t const cRegCount = 32;

	size_t const cInstructionIncrement = 1;
	size_t const cDataIncrement = 2;

	size_t const cMemInstructionSize = (1 << 16) / cInstructionIncrement;
	size_t const cMemDataSize = (1 << 16) / cDataIncrement;

	size_t const cSizeInstruction = 16;
	size_t const cPosOpcode = 10;
	size_t const cPosRegRa = 5;
	size_t const cPosRegRb = 0;

	enum TOpcode {
		eNop      = 0x00,
		eSleep    = 0x01,
		eLoadi    = 0x02,
		eLoad     = 0x03,
		eStore    = 0x04,
		eJump     = 0x08,
		eJumpc    = 0x0A,
		eJumpz    = 0x0B,
		eMove     = 0x0C,
		eAnd      = 0x10,
		eOr       = 0x11,
		eXor      = 0x12,
		eNot      = 0x13,
		eAdd      = 0x14,
		eAddc     = 0x15,
		eSub      = 0x16,
		eSubc     = 0x17,
		eComp     = 0x18,
		eInc      = 0x1A,
		eDec      = 0x1B,
		eShl      = 0x1C,
		eShr      = 0x1D,
		eShlc     = 0x1E,
		eShrc     = 0x1F,
		ePrintInt = 0x3E
	};

	TOpcode MaskOpcode(TInstruction const instruction);
	size_t MaskRegRa(TInstruction const instruction);
	size_t MaskRegRb(TInstruction const instruction);
	TInstruction GenInsturction(TOpcode const opcode, size_t const raIdx, size_t const rbIdx);

}

#endif
