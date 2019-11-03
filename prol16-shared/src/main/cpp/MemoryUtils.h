/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Various memory utilities.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_MEMORYUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_MEMORYUTILS_H_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util { namespace memory {

using Data = uint16_t;
using Address = uint16_t;
using Segment = std::vector<Data>;

unsigned calcStringSpaceInMemory(std::string const &str);

}	// namespace memory
}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_MEMORYUTILS_H_INCLUDED */
