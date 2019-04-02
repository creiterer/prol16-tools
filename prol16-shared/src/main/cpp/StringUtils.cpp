/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "StringUtils.h"

#include <algorithm>
#include <stdexcept>

namespace util {

namespace preconditions {

void checkStringIsNotEmpty(std::string const &str) {
	if (str.empty()) {
		throw std::invalid_argument("empty string argument");
	}
}

}

std::string toLower(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

void prepend(std::string &str, char const c) {
	str.insert(str.begin(), c);
}

std::string prepend(std::string const &str, char const c) {
	std::string s(str);
	prepend(s, c);

	return s;
}

void prepend(std::string &str, std::string const &prependee) {
	str.insert(0, prependee);
}

std::string prepend(std::string const &str, std::string const &prependee) {
	std::string s(str);
	prepend(s, prependee);

	return s;
}

}
