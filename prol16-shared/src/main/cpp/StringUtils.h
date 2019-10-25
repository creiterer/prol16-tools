/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED

#include "MathUtils.h"

#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

namespace util {

namespace preconditions {

void checkStringIsNotEmpty(std::string const &str);

}	// namespace preconditions

std::string toLower(std::string str);
std::string toUpper(std::string str);

void prepend(std::string &str, char const c);
std::string prepend(std::string const &str, char const c);

void prepend(std::string &str, std::string const &prependee);
std::string prepend(std::string const &str, std::string const &prependee);

void ltrim(std::string &str, std::string const &chars);
std::string ltrim(std::string const &str, std::string const &chars);

void rtrim(std::string &str, std::string const &chars);

void trim(std::string &str, std::string const &chars);

void trimQuotes(std::string &str);

std::string getUnquoted(std::string str);
std::string getQuoted(std::string const &str);

std::string handleEscapeSequences(std::string str);
std::string getEscaped(std::string str);

void pad(std::string &str, unsigned const alignment);
std::string getPadded(std::string str, unsigned const alignment);

template <typename T>
std::vector<T> encode(std::string str) {
	static_assert(std::is_integral<T>::value, "encode() requires an integral value type for the returned buffer.");

	pad(str, sizeof(T));
	size_t const cStringLength = str.length() + 1;	// +1 for '\0'
	assert(util::isMultiple(sizeof(T), cStringLength));

	std::vector<T> buffer(cStringLength / sizeof(T));
	std::memcpy(buffer.data(), str.c_str(), cStringLength);

	return buffer;
}

template <typename... Args>
std::string format(char const * const formatString, Args const... args) {
	size_t const bufferSize = 100;
	std::array<char, bufferSize> buffer = {0};

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
	snprintf(buffer.data(), bufferSize, formatString, args...);

	return buffer.data();
}

}	// namespace util

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED */
