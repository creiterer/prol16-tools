/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Various math utilities.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_MATHUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_MATHUTILS_H_INCLUDED

#include <stdexcept>

namespace util {

/**
 * Check if b is a multiple of a.
 * @param a
 * @param b
 * @return	True if b = n*a, false otherwise.
 */
template <typename T>
bool isMultiple(T const a, T const b) {
	if (a == 0) {
		throw std::invalid_argument("'a' is 0");
	}

	return (b % a) == 0;
}

}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_MATHUTILS_H_INCLUDED */
