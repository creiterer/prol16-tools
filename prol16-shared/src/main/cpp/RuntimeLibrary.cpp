/**
 * @author		creiterer
 * @date 		2019-10-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		This module contains functionality regarding the PROL16 runtime library.
 */

#include "RuntimeLibrary.h"

#include "StringUtils.h"

#include <algorithm>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace rtlib {

PROL16::util::memory::Address getRuntimeLibFunctionAddress(std::string const &functionName) {
	return RuntimeLibFunctions.at(functionName);
}

std::string getRuntimeLibFunctionName(PROL16::util::memory::Address const address) {
	auto found = std::find_if(RuntimeLibFunctions.cbegin(), RuntimeLibFunctions.cend(), [address](RuntimeLibFunctionTable::value_type const &rtlibEntry){
		return rtlibEntry.second == address;
	});

	if (found == RuntimeLibFunctions.cend()) {
		throw std::out_of_range(::util::format("0x%04hX is not a runtime library function address", address));
	}

	return found->first;
}

std::string getRuntimeLibFunctionName(RuntimeLibFunctionAddress const address) {
	return getRuntimeLibFunctionName(static_cast<PROL16::util::memory::Address>(address));
}

bool isRuntimeLibFunctionAddress(PROL16::util::memory::Address const address) {
	return std::any_of(RuntimeLibFunctions.cbegin(), RuntimeLibFunctions.cend(), [address](RuntimeLibFunctionTable::value_type const &rtlibEntry){
		return rtlibEntry.second == address;
	});
}

bool isDiv32(PROL16::util::memory::Address const address) noexcept {
	return (address == SDIV_I32) || (address == UDIV_I32);
}

bool isRem32(PROL16::util::memory::Address const address) noexcept {
	return (address == SREM_I32) || (address == UREM_I32);
}

}	// namespace rtlib
}	// namespace PROL16

