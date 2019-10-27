/**
 * @author		creiterer
 * @date 		2019-10-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_RUNTIMELIBRARY_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_RUNTIMELIBRARY_H_INCLUDED

#include "MemoryUtils.h"

#include <string>
#include <unordered_map>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace rtlib {

using RuntimeLibFunctionTable = std::unordered_map<std::string, PROL16::util::memory::Address>;

enum RuntimeLibFunctionAddress : PROL16::util::memory::Address {
	PRINT = 0x7FFF,
	PRINTSTR = 0x7FFE,
	MUL = 0x7FFD,
	DIV = 0x7FFC,
	DIVU = 0x7FFB,
	MOD = 0x7FFA,
	MODU = 0x7FF9,
	PRINT32 = 0x7FF8,
};

static RuntimeLibFunctionTable const RuntimeLibFunctions = {
		{"_print", PRINT},
		{"_printstr", PRINTSTR},
		{"_mul", MUL},
		{"_div", DIV},
		{"_divu", DIVU},
		{"_mod", MOD},
		{"_modu", MODU},
		{"_print32", PRINT32}
};

PROL16::util::memory::Address getRuntimeLibFunctionAddress(std::string const &functionName);
std::string getRuntimeLibFunctionName(RuntimeLibFunctionAddress const address);

bool isRuntimeLibFunctionAddress(PROL16::util::memory::Address const address);

}	// namespace rtlib
}	// namespace PROL16



#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_RUNTIMELIBRARY_H_INCLUDED */
