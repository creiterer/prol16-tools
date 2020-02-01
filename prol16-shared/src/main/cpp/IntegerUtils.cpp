/**
 * @author		creiterer
 * @date 		2020-01-15
 * @copyright 	Copyright (c) 2020 Christopher Reiterer
 * @brief 		Utility functions for integers.
 */

#include "IntegerUtils.h"

namespace util { namespace integer {

uint32_t mergeValues(uint16_t const highValue, uint16_t const lowValue) noexcept {
	return (static_cast<uint32_t>(highValue) << 16) + lowValue;
}

}	// namespace integer
} 	// namespace util
