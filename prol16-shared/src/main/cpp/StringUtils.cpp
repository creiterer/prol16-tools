/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utility functions for string manipulation.
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

}	// namespace preconditions

std::string toLower(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

std::string toUpper(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

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
	return prependee + str;
}

void ltrim(std::string &str, std::string const &chars) {
	size_t const pos = str.find_first_not_of(chars);
	str.erase(0, pos);
}

std::string ltrim(std::string const &str, std::string const &chars) {
	std::string s(str);
	ltrim(s, chars);

	return s;
}

void rtrim(std::string &str, std::string const &chars) {
	size_t const pos = str.find_last_not_of(chars) + 1;
	if (pos <= str.length()) {
		str.erase(pos, str.length() - pos);
	}
}

void trim(std::string &str, std::string const &chars) {
	ltrim(str, chars);
	rtrim(str, chars);
}

void trimQuotes(std::string &str) {
	trim(str, "\"");
}

std::string getUnquoted(std::string str) {
	trimQuotes(str);

	return str;
}

std::string getQuoted(std::string const &str) {
	return '"' + str + '"';
}

std::string handleEscapeSequences(std::string str) {
	size_t pos = str.find('\\');
	while (pos != std::string::npos) {
		if (pos + 1 < str.length()) {
			switch (str[pos+1]) {
			case 'n': str.replace(pos, 2, "\n"); break;
			case 'r': str.replace(pos, 2, "\r"); break;
			case 't': str.replace(pos, 2, "\t"); break;
			}
		}
		pos = str.find('\\', pos + 1);
	}

	return str;
}

std::string getEscaped(std::string str) {
	size_t pos = str.find_first_of("\n\r\t");
	while (pos != std::string::npos) {
		switch (str[pos]) {
		case '\n': str.replace(pos, 1, "\\n"); break;
		case '\r': str.replace(pos, 1, "\\r"); break;
		case '\t': str.replace(pos, 1, "\\t"); break;
		}

		pos = str.find_first_of("\n\r\t", pos + 2);
	}

	return str;
}

std::string getPadded(std::string str, unsigned const alignment) {
	pad(str, alignment);
	return str;
}

void pad(std::string &str, unsigned const alignment) {
	while (((str.length() + 1) % alignment) != 0) {
		str.push_back('\0');
	}
}

}	// namespace util
