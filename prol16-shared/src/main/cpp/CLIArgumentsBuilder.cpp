/**
 * @author		creiterer
 * @date 		2019-08-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class used to build an instance of CLIArguments.
 */

#include "CLIArgumentsBuilder.h"

namespace util { namespace cli {

CLIArguments CLIArgumentsBuilder::build() const {
	return CLIArguments(arguments, flags, shortToLongNameMap);
}

void CLIArgumentsBuilder::addArgument(std::string const &name, std::string const &value) {
	arguments.emplace(name, value);
}

void CLIArgumentsBuilder::addFlag(std::string const &name, bool const value) {
	flags.emplace(name, value);
}

}	// namespace cli
}	// namespace util
