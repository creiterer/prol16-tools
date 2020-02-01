/**
 * @author		creiterer
 * @date 		2020-01-21
 * @copyright 	Copyright (c) 2020 Christopher Reiterer
 * @brief 		Go runtime functions.
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_GORUNTIME_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_GORUNTIME_H_INCLUDED

#include "RegisterFile.h"
#include "VirtualMemory.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace go { namespace rtlib {

void goNew(RegisterFile &registerFile, VirtualMemory &virtualMemory);

}	// namespace rtlib
}	// namespace go
}	// namespace PROL16



#endif /* PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_GORUNTIME_H_INCLUDED */
