/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED

#include <string>

namespace util {

namespace preconditions {

void checkStringIsNotEmpty(std::string const &str);

}	// namespace preconditions

std::string toLower(std::string str);

void prepend(std::string &str, char const c);
std::string prepend(std::string const &str, char const c);

void prepend(std::string &str, std::string const &prependee);
std::string prepend(std::string const &str, std::string const &prependee);

}	// namespace util

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_STRINGUTILS_H_INCLUDED */
