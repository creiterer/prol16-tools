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
	/// print stuff (0x7FF*)
	PRINT_UINT16 = 0x7FFF,
	PRINT_UINT32 = 0x7FFE,
	PRINT_RUNE = 0x7FFD,
	PRINT_STRING = 0x7FFC,
	PRINT_POINTER = 0x7FFB,
	PRINT_NL = 0x7FFA,
	PRINT_SPACE = 0x7FF9,

	/// arithmetic stuff (0x7FE*)
	MUL_I16 = 0x7FEF,
	SDIV_I16 = 0x7FEE,
	UDIV_I16 = 0x7FED,
	SREM_I16 = 0x7FEC,
	UREM_I16 = 0x7FEB,
	MUL_I32 = 0x7FEA,
	SDIV_I32 = 0x7FE9,
	UDIV_I32 = 0x7FE8,
	SREM_I32 = 0x7FE7,
	UREM_I32 = 0x7FE6,

	/// memory stuff (0x7FD*)
	MEMCPY = 0x7FDF,
	MEMSET = 0x7FDE,
	SBRK = 0x7FDD,

	/// Go-specific stuff (0x7FC*)
	GO_RUNTIME_ERROR = 0x7FCF,
	GO_NEW = 0x7FCE,
	GO_TYPE_HASH_IDENTITY =0x7FCD,
	GO_TYPE_HASH_IDENTITY_DESCRIPTOR =0x7FCC,
	GO_TYPE_HASH_INTERFACE =0x7FCB,
	GO_TYPE_HASH_INTERFACE_DESCRIPTOR =0x7FCA,
	GO_TYPE_HASH_ERROR_DESCRIPTOR =0x7FC9,
	GO_TYPE_EQUAL_IDENTITY =0x7FC8,
	GO_TYPE_EQUAL_IDENTITY_DESCRIPTOR =0x7FC7,
	GO_TYPE_EQUAL_INTERFACE =0x7FC6,
	GO_TYPE_EQUAL_INTERFACE_DESCRIPTOR =0x7FC5,
	GO_TYPE_EQUAL_ERROR_DESCRIPTOR =0x7FC4,
};

static RuntimeLibFunctionTable const RuntimeLibFunctions = {
		/// print stuff
		{"__prol16_print_uint16", PRINT_UINT16},
		{"__prol16_print_uint32", PRINT_UINT32},
		{"__prol16_print_rune", PRINT_RUNE},
		{"__prol16_print_string", PRINT_STRING},
		{"__prol16_print_pointer", PRINT_POINTER},
		{"__prol16_print_nl", PRINT_NL},
		{"__prol16_print_space", PRINT_SPACE},

		/// arithmetic stuff -- keep in sync with PROL16ISelLowering
		{"__prol16_mul_i16", MUL_I16},
		{"__prol16_sdiv_i16", SDIV_I16},
		{"__prol16_udiv_i16", UDIV_I16},
		{"__prol16_srem_i16", SREM_I16},
		{"__prol16_urem_i16", UREM_I16},
		{"__prol16_mul_i32", MUL_I32},
		{"__prol16_sdiv_i32", SDIV_I32},
		{"__prol16_udiv_i32", UDIV_I32},
		{"__prol16_srem_i32", SREM_I32},
		{"__prol16_urem_i32", UREM_I32},

		/// memory stuff
		{"memcpy", MEMCPY},
		{"memset", MEMSET},
		{"__prol16_sbrk", SBRK},

		/// Go-specific stuff
		{"__go_runtime_error", GO_RUNTIME_ERROR},
		{"__go_new", GO_NEW},
		{"__go_type_hash_identity", GO_TYPE_HASH_IDENTITY},
		{"__go_type_hash_identity_descriptor", GO_TYPE_HASH_IDENTITY_DESCRIPTOR},
		{"__go_type_hash_interface", GO_TYPE_HASH_INTERFACE},
		{"__go_type_hash_interface_descriptor", GO_TYPE_HASH_INTERFACE_DESCRIPTOR},
		{"__go_type_hash_error_descriptor", GO_TYPE_HASH_ERROR_DESCRIPTOR},
		{"__go_type_equal_identity", GO_TYPE_EQUAL_IDENTITY},
		{"__go_type_equal_identity_descriptor", GO_TYPE_EQUAL_IDENTITY_DESCRIPTOR},
		{"__go_type_equal_interface", GO_TYPE_EQUAL_INTERFACE},
		{"__go_type_equal_interface_descriptor", GO_TYPE_EQUAL_INTERFACE_DESCRIPTOR},
		{"__go_type_equal_error_descriptor", GO_TYPE_EQUAL_ERROR_DESCRIPTOR}
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
