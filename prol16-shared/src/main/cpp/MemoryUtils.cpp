/**
 * @author		creiterer
 * @date 		2019-10-07
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Various memory utilities.
 */

#include "MemoryUtils.h"

#include "MathUtils.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util { namespace memory {

unsigned calcStringSpaceInMemory(std::string const &str) {
	size_t const cStringLength = str.length() + 1;

	if (!::util::isMultiple(sizeof(Data), cStringLength)) {
		return (cStringLength / sizeof(Data)) + 1;
	}

	return cStringLength / sizeof(Data);
}

}	// namespace memory
}	// namespace util
}	// namespace PROL16
