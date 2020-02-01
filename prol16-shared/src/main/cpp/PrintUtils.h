/**
 * @author		creiterer
 * @date 		2019-10-27
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utilities for printing.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PRINTUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PRINTUTILS_H_INCLUDED

#include "StringUtils.h"

#include <ostream>
#include <type_traits>

namespace util {

template <typename T>
std::ostream& printHexNumberFormatted(std::ostream &stream, T const number) {
	static_assert(std::is_integral<T>::value, "printHexNumberFormatted() requires an integral value type for the number to be printed.");

	stream << formatAsHexNumber(number);

	return stream;
}

template <typename T>
std::ostream& printHexNumberFormattedWithBase(std::ostream &stream, T const number) {
	static_assert(std::is_integral<T>::value, "printHexNumberFormattedWithBase() requires an integral value type for the number to be printed.");

	stream << formatAsHexNumberWithBase(number);

	return stream;
}

} 	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PRINTUTILS_H_INCLUDED */
