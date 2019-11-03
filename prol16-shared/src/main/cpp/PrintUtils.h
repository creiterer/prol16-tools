/**
 * @author		creiterer
 * @date 		2019-10-27
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utilities for printing.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PRINTUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PRINTUTILS_H_INCLUDED

#include <iomanip>
#include <ostream>
#include <type_traits>

namespace util {

template <typename T>
std::ostream& printHexNumberFormatted(std::ostream &stream, T const number) {
	static_assert(std::is_integral<T>::value, "printHexNumberFormatted() requires an integral value type for the number to be printed.");

	stream << std::hex << std::uppercase << std::setfill('0') << std::setw(sizeof(T) * 2) << number;

	return stream;
}

template <typename T>
std::ostream& printHexNumberFormattedWithBase(std::ostream &stream, T const number) {
	static_assert(std::is_integral<T>::value, "printHexNumberFormattedWithBase() requires an integral value type for the number to be printed.");

	return printHexNumberFormatted(stream << "0x", number);
}

} 	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PRINTUTILS_H_INCLUDED */
