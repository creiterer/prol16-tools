/**
 * @author		creiterer
 * @date 		2019-10-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		This file contains some standard (i.e. used across all prol16 tools)
 * 				CLI argument names for options and flags.
 */

#include "CLIArgumentNames.h"

bool operator==(std::string const &lhs, ::util::cli::ArgumentName const &rhs) {
	return (lhs == rhs.shortName) || (lhs == rhs.longName);
}

bool operator==(::util::cli::ArgumentName const &lhs, std::string const &rhs) {
	return operator==(rhs, lhs);
}
