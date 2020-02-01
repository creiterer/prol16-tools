/**
 * @author		creiterer
 * @date 		2020-01-15
 * @copyright 	Copyright (c) 2020 Christopher Reiterer
 * @brief 		Utility functions for integers.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_INTEGERUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_INTEGERUTILS_H_INCLUDED

#include <cstdint>

namespace util { namespace integer {

uint32_t mergeValues(uint16_t const highValue, uint16_t const lowValue) noexcept;

}	// namespace integer
} 	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_INTEGERUTILS_H_INCLUDED */
