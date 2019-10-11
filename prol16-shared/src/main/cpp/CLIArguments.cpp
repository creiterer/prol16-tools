/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "CLIArguments.h"

#include <stdexcept>
#include <utility>

namespace util { namespace cli {

CLIArguments::CLIArguments(ArgumentMap arguments, FlagMap flags, ArgumentMap shortToLongNameMap)
: arguments(std::move(arguments)), flags(std::move(flags)), shortToLongNameMap(std::move(shortToLongNameMap)) {}

bool CLIArguments::isSet(std::string const &flagName) const {
	try {
		// assume flagName is the long name
		return flags.at(flagName);
	} catch (std::out_of_range const&) {
		// flagName was not the long name -> assume it is the short name -> try to map it to the long name
		return flags.at(shortToLongNameMap.at(flagName));
	}
}

bool CLIArguments::isSet(ArgumentName const &flagName) const {
	return flags.at(flagName.longName);
}

std::string const& CLIArguments::operator[](std::string const &argumentName) const {
	try {
		// assume argumentName is the long name
		return arguments.at(argumentName);
	} catch (std::out_of_range const&) {
		// argumentName was not the long name -> assume it is the short name -> try to map it to the long name
		return arguments.at(shortToLongNameMap.at(argumentName));
	}
}

std::string const& CLIArguments::operator[](ArgumentName const &argumentName) const {
	return operator[](argumentName.longName);
}

}	// namespace cli
}	// namespace util
