/**
 * @author		creiterer
 * @date 		2019-12-03
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utilities for handling programming-language-dependent characteristics.
 */

#include "Flavor.h"

#include "StringUtils.h"

namespace util {

Flavor determineFlavor(std::string const &flavor) {
	if (toLower(flavor) == "c") {
		return Flavor::C;
	}

	if (toLower(flavor) == "go") {
		return Flavor::Go;
	}

	return Flavor::Unknown;
}

std::string getFlavorAsString(Flavor const flavor) {
	switch (flavor) {
	case Flavor::C: return "C";
	case Flavor::Go: return "Go";
	default: return "Unknown";
	}
}

} 	// namespace util
