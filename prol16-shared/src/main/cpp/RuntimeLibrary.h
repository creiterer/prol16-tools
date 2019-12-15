/**
 * @author		creiterer
 * @date 		2019-10-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		This module contains functionality regarding the PROL16 runtime library.
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
	PRINT_UINT16 = 0x7FFF,
	PRINT_UINT32 = 0x7FFE,
	PRINT_RUNE = 0x7FFD,
	PRINT_STRING = 0x7FFC,
	PRINT_NL = 0x7FFB,
	PRINT_SPACE = 0x7FFA,
	MUL_I16 = 0x7FF9,
	SDIV_I16 = 0x7FF8,
	UDIV_I16 = 0x7FF7,
	SREM_I16 = 0x7FF6,
	UREM_I16 = 0x7FF5,
	MUL_I32 = 0x7FF4,
	SDIV_I32 = 0x7FF3,
	UDIV_I32 = 0x7FF2,
	SREM_I32 = 0x7FF1,
	UREM_I32 = 0x7FF0,
};

static RuntimeLibFunctionTable const RuntimeLibFunctions = {
		{"__prol16_print_uint16", PRINT_UINT16},
		{"__prol16_print_uint32", PRINT_UINT32},
		{"__prol16_print_rune", PRINT_RUNE},
		{"__prol16_print_string", PRINT_STRING},
		{"__prol16_print_nl", PRINT_NL},
		{"__prol16_print_space", PRINT_SPACE},
		// keep the following in sync with PROL16ISelLowering
		{"__prol16_mul_i16", MUL_I16},
		{"__prol16_sdiv_i16", SDIV_I16},
		{"__prol16_udiv_i16", UDIV_I16},
		{"__prol16_srem_i16", SREM_I16},
		{"__prol16_urem_i16", UREM_I16},
		{"__prol16_mul_i32", MUL_I32},
		{"__prol16_sdiv_i32", SDIV_I32},
		{"__prol16_udiv_i32", UDIV_I32},
		{"__prol16_srem_i32", SREM_I32},
		{"__prol16_urem_i32", UREM_I32}
};

PROL16::util::memory::Address getRuntimeLibFunctionAddress(std::string const &functionName);
std::string getRuntimeLibFunctionName(RuntimeLibFunctionAddress const address);
std::string getRuntimeLibFunctionName(PROL16::util::memory::Address const address);

bool isRuntimeLibFunctionAddress(PROL16::util::memory::Address const address);

bool isDiv32(PROL16::util::memory::Address const address) noexcept;
bool isRem32(PROL16::util::memory::Address const address) noexcept;

}	// namespace rtlib
}	// namespace PROL16



#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_RUNTIMELIBRARY_H_INCLUDED */
