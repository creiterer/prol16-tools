/**
 * @author		creiterer
 * @date 		2019-12-03
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utilities for handling programming-language-dependent characteristics.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FLAVOR_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FLAVOR_H_INCLUDED

#include <string>

namespace util {

enum class Flavor {
	C,
	Go,
	Unknown,
};

Flavor determineFlavor(std::string const &flavor);

std::string getFlavorAsString(Flavor const flavor);

} 	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FLAVOR_H_INCLUDED */
