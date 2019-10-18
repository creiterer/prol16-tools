/**
 * @author		creiterer
 * @date 		2019-10-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
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

std::string getRuntimeLibFunctionName(RuntimeLibFunctionAddress const address) {
	auto found = std::find_if(RuntimeLibFunctions.cbegin(), RuntimeLibFunctions.cend(), [address](RuntimeLibFunctionTable::value_type const &rtlibEntry){
		return rtlibEntry.second == address;
	});

	if (found == RuntimeLibFunctions.cend()) {
		throw std::out_of_range(::util::format("0x%04hX is not a runtime library function address", address));
	}

	return found->first;
}

bool isRuntimeLibFunctionAddress(PROL16::util::memory::Address const address) {
	return std::any_of(RuntimeLibFunctions.cbegin(), RuntimeLibFunctions.cend(), [address](RuntimeLibFunctionTable::value_type const &rtlibEntry){
		return rtlibEntry.second == address;
	});
}

}	// namespace rtlib
}	// namespace PROL16

