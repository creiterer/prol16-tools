/**
 * @author		creiterer
 * @date 		2020-01-21
 * @copyright 	Copyright (c) 2020 Christopher Reiterer
 * @brief 		Go runtime functions.
 */

#include "GoRuntime.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace go { namespace rtlib {

void goNew(RegisterFile &registerFile, VirtualMemory &virtualMemory) {
	constexpr RegisterFile::Register dstReg = 4;
	constexpr RegisterFile::Register sizeReg = 6;

	registerFile[dstReg] = virtualMemory.incrementHeapBreak(registerFile[sizeReg]);
}

}	// namespace rtlib
}	// namespace go
}	// namespace PROL16
