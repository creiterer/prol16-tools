/**
 * @author		creiterer
 * @date 		2019-10-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "RuntimeLibrary.h"

#include <algorithm>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace rtlib {

PROL16::util::memory::Address getRuntimeLibFunctionAddress(std::string const &functionName) {
	return RuntimeLibFunctions.at(functionName);
}

bool isRuntimeLibFunctionAddress(PROL16::util::memory::Address const address) {
	return std::any_of(RuntimeLibFunctions.cbegin(), RuntimeLibFunctions.cend(), [address](RuntimeLibFunctionTable::value_type const &rtlibEntry){
		return rtlibEntry.second == address;
	});
}

}	// namespace rtlib
}	// namespace PROL16

