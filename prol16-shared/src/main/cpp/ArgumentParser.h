/**
 * @author		creiterer
 * @date 		2019-08-03
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class for parsing CLI arguments in a convenient way.
 * @details		Inspired by https://docs.python.org/2/library/argparse.html#module-argparse
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARGUMENTPARSER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARGUMENTPARSER_H_INCLUDED

#include "CLIArgumentNames.h"
#include "CLIArguments.h"
#include "CLIArgumentsBuilder.h"
#include "NonCopyable.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace util { namespace cli {

class ArgumentParser final : private NonCopyable {
public:
	using ArgumentVector = std::vector<std::string>;
	using ArgumentMap = CLIArgumentsBuilder::ArgumentMap;
	using FlagMap = CLIArgumentsBuilder::FlagMap;

	explicit ArgumentParser(std::string description = "");

	ArgumentParser& addPositionalArgument(std::string const &name);

	ArgumentParser& addOptionalArgument(std::string const &longName, std::string const &defaultValue);
	ArgumentParser& addOptionalArgument(std::string const &shortName, std::string const &longName, std::string const &defaultValue);
	ArgumentParser& addOptionalArgument(ArgumentName const &optionName, std::string const &defaultValue);

	ArgumentParser& addFlag(std::string const &longName, bool const defaultValue = false);
	ArgumentParser& addFlag(std::string const &shortName, std::string const &longName, bool const defaultValue = false);
	ArgumentParser& addFlag(ArgumentName const &flagName, bool const defaultValue = false);

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, modernize-avoid-c-arrays)
	CLIArguments parseArguments(int const argc, char const * const argv[]);

	std::string getUsageMessage() const;
	void showUsageMessage(std::ostream &stream) const;

private:
	// at positional arguments the position of the argument matters
	// -> something that preserves the order is required -> vector
	ArgumentVector positionalArguments;
	ArgumentMap optionalArguments;
	FlagMap flags;

	ArgumentMap shortToLongNameMapping;

	std::string appName;
	std::string const description;
};

}	// namespace cli
}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARGUMENTPARSER_H_INCLUDED */
