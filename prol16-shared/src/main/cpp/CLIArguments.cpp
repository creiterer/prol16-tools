/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "CLIArguments.h"

#include <stdexcept>

namespace util { namespace cli {

CLIArguments::CLIArguments(ArgumentMap const &arguments, FlagMap const &flags, ArgumentMap const &shortToLongNameMap)
: arguments(arguments), flags(flags), shortToLongNameMap(shortToLongNameMap) {}

bool CLIArguments::isSet(std::string const &flagName) const {
	try {
		// assume flagName is the long name
		return flags.at(flagName);
	} catch (std::out_of_range const&) {
		// flagName was not the long name -> assume it is the short name -> try to map it to the long name
		return flags.at(shortToLongNameMap.at(flagName));
	}
}

bool CLIArguments::isSet(flags::FlagName const &flagName) const {
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

}}
