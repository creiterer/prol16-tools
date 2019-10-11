/**
 * @author		creiterer
 * @date 		2019-08-03
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class for parsing CLI arguments in a convenient way.
 * @details		Inspired by https://docs.python.org/2/library/argparse.html#module-argparse
 */

#include "ArgumentParser.h"

#include "CLIArguments.h"
#include "CLIArgumentsBuilder.h"
#include "CLIError.h"

#include <algorithm>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

namespace util { namespace cli {

ArgumentParser& ArgumentParser::addPositionalArgument(std::string const &name) {
	assert(!name.empty());
	assert(std::none_of(positionalArguments.cbegin(), positionalArguments.cend(), [&name](std::string const &element){return name == element;}));

	positionalArguments.emplace_back(name);

	return *this;
}

ArgumentParser& ArgumentParser::addOptionalArgument(std::string const &longName, std::string const &defaultValue) {
	assert(!longName.empty());

	auto const result = optionalArguments.emplace(longName, defaultValue);
	assert(result.second);

	return *this;
}

ArgumentParser& ArgumentParser::addOptionalArgument(std::string const &shortName, std::string const &longName, std::string const &defaultValue) {
	assert(!shortName.empty());
	assert(!longName.empty());

	auto const result = optionalArguments.emplace(longName, defaultValue);
	assert(result.second);

	auto const result2 = shortToLongNameMapping.emplace(shortName, longName);
	assert(result2.second);

	return *this;
}

ArgumentParser& ArgumentParser::addOptionalArgument(ArgumentName const &optionName, std::string const &defaultValue) {
	return addOptionalArgument(optionName.shortName, optionName.longName, defaultValue);
}

ArgumentParser& ArgumentParser::addFlag(std::string const &longName, bool const defaultValue) {
	assert(!longName.empty());

	auto const result = flags.emplace(longName, defaultValue);
	assert(result.second);

	return *this;
}

ArgumentParser& ArgumentParser::addFlag(std::string const &shortName, std::string const &longName, bool const defaultValue) {
	assert(!shortName.empty());
	assert(!longName.empty());

	auto const result = flags.emplace(longName, defaultValue);
	assert(result.second);

	auto const result2 = shortToLongNameMapping.emplace(shortName, longName);
	assert(result2.second);

	return *this;
}

ArgumentParser& ArgumentParser::addFlag(ArgumentName const &flagName, bool const defaultValue) {
	return addFlag(flagName.shortName, flagName.longName, defaultValue);
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, modernize-avoid-c-arrays)
CLIArguments ArgumentParser::parseArguments(int const argc, char const * const argv[]) const {
	ArgumentVector positionalArgumentsCopy = positionalArguments;
	ArgumentMap optionalArgumentsCopy = optionalArguments;
	FlagMap flagsCopy = flags;

	CLIArgumentsBuilder cliArgumentsBuilder;
	cliArgumentsBuilder.addShortToLongNameMapping(shortToLongNameMapping);

	for (int i = 1; i < argc; ++i) {
		std::string const argumentValue = argv[i];
		std::string longOptionName;

		try {
			longOptionName = shortToLongNameMapping.at(argumentValue);
		} catch (std::out_of_range const&) {
			longOptionName = argumentValue;
		}


		if (flagsCopy.find(longOptionName) != flagsCopy.cend()) {
			cliArgumentsBuilder.addFlag(longOptionName, !flagsCopy.at(longOptionName));
			flagsCopy.erase(longOptionName);
		} else if (optionalArgumentsCopy.find(longOptionName) != optionalArgumentsCopy.cend()) {
			// check if the required value of the optional argument is provided
			if (argc <= i + 1) {
				std::ostringstream errorMessage;
				errorMessage << "no value provided for '" << argumentValue << "'";
				throw CLIError(errorMessage.str(), getUsageMessage(argv[0]));
			}

			cliArgumentsBuilder.addArgument(longOptionName, argv[++i]);
			optionalArgumentsCopy.erase(longOptionName);
		} else if (!positionalArgumentsCopy.empty()) {
			cliArgumentsBuilder.addArgument(positionalArgumentsCopy[0], argumentValue);
			positionalArgumentsCopy.erase(positionalArgumentsCopy.begin());
		} else {
			std::ostringstream errorMessage;
			errorMessage << "invalid argument '" << argumentValue << "'";
			throw CLIError(errorMessage.str(), getUsageMessage(argv[0]));
		}
	}

	// check if all positional arguments were covered
	if (!positionalArgumentsCopy.empty()) {
		throw CLIError("not all positional arguments were specified", getUsageMessage(argv[0]));
	}

	// add default values of the optional arguments
	for (auto const &argument : optionalArgumentsCopy) {
		cliArgumentsBuilder.addArgument(argument.first, argument.second);
	}

	// add default values of flags
	for (auto const &flag : flagsCopy) {
		cliArgumentsBuilder.addFlag(flag.first, flag.second);
	}

	return cliArgumentsBuilder.build();
}

std::string ArgumentParser::getUsageMessage(std::string const &appName) const {
	std::ostringstream usageMessage;
	usageMessage << "Usage: " << appName;

	std::unordered_set<ArgumentMap::mapped_type> alreadyCoveredLongNames;

	for (auto const &argument : shortToLongNameMapping) {
		usageMessage << " [" << argument.first << ", " << argument.second << "]";
		alreadyCoveredLongNames.emplace(argument.second);
	}

	for (auto const &flag : flags) {
		if (alreadyCoveredLongNames.find(flag.first) == alreadyCoveredLongNames.cend()) {
			usageMessage << " [" << flag.first << "]";
		}
	}

	for (auto const &argument : optionalArguments) {
		if (alreadyCoveredLongNames.find(argument.first) == alreadyCoveredLongNames.cend()) {
			usageMessage << " [" << argument.first << "]";
		}
	}

	for (auto const &argument : positionalArguments) {
		usageMessage << " " << argument;
	}

	return usageMessage.str();
}

}	// namespace cli
}	// namespace util
