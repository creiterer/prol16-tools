/**
 * @author		creiterer
 * @date 		2019-08-03
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class for parsing CLI arguments in a convenient way.
 * @details		Inspired by https://docs.python.org/2/library/argparse.html#module-argparse
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARGUMENTPARSER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARGUMENTPARSER_H_INCLUDED

#include <string>
#include <unordered_map>
#include <vector>

#include "NonCopyable.h"
#include "CLIArguments.h"
#include "CLIArgumentsBuilder.h"
#include "CLIFlags.h"

namespace util { namespace cli {

class ArgumentParser final : private NonCopyable {
public:
	using ArgumentVector = std::vector<std::string>;
	using ArgumentMap = CLIArgumentsBuilder::ArgumentMap;
	using FlagMap = CLIArgumentsBuilder::FlagMap;

	ArgumentParser() = default;
	~ArgumentParser() = default;

	ArgumentParser& addPositionalArgument(std::string const &name);

	ArgumentParser& addOptionalArgument(std::string const &longName);
	ArgumentParser& addOptionalArgument(std::string const &shortName, std::string const &longName);

	ArgumentParser& addFlag(std::string const &longName, bool const defaultValue);
	ArgumentParser& addFlag(std::string const &shortName, std::string const &longName, bool const defaultValue);
	ArgumentParser& addFlag(flags::FlagName const &flagName, bool const defaultValue);

	CLIArguments parseArguments(int const argc, char const * const argv[]) const;

	std::string getUsageMessage(std::string const &appName) const;

private:
	// at positional arguments the position of the argument matters
	// -> something that preserves the order is required -> vector
	ArgumentVector positionalArguments;
	ArgumentMap optionalArguments;
	FlagMap flags;

	ArgumentMap shortToLongNameMapping;
};

}}

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARGUMENTPARSER_H_INCLUDED */
