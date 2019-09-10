/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED

#include "MathUtils.h"

#include <cassert>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

namespace util {

namespace preconditions {

void checkStringIsNotEmpty(std::string const &str);

}	// namespace preconditions

std::string toLower(std::string str);

void prepend(std::string &str, char const c);
std::string prepend(std::string const &str, char const c);

void prepend(std::string &str, std::string const &prependee);
std::string prepend(std::string const &str, std::string const &prependee);

void ltrim(std::string &str, std::string const &chars);

void rtrim(std::string &str, std::string const &chars);

void trim(std::string &str, std::string const &chars);

void trimQuotes(std::string &str);

std::string getUnquoted(std::string str);

std::string handleEscapeSequences(std::string str);

template <typename T>
std::vector<T> encode(std::string str) {
	static_assert(std::is_integral<T>::value, "encode() requires an integral value type for the returned buffer.");

	while (((str.length() + 1) % sizeof(T)) != 0) {
		str.push_back('\0');
	}
	size_t const cStringLength = str.length() + 1;	// +1 for '\0'
	assert(util::isMultiple(sizeof(T), cStringLength));

	std::vector<T> buffer(cStringLength / sizeof(T));
	std::memcpy(buffer.data(), str.c_str(), cStringLength);

	return buffer;
}

}	// namespace util

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED */
