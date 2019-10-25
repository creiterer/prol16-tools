/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTS_H_INCLUDED

#include "CLIArgumentNames.h"

#include <string>
#include <unordered_map>

namespace util { namespace cli {

class CLIArguments final {
public:
	using ArgumentMap = std::unordered_map<std::string, std::string>;
	using FlagMap = std::unordered_map<std::string, bool>;

	explicit CLIArguments(bool const isHelp);
	CLIArguments(ArgumentMap arguments, FlagMap flags, ArgumentMap shortToLongNameMap);

	bool isSet(std::string const &flagName) const;
	bool isSet(ArgumentName const &flagName) const;
	std::string const& operator[](std::string const &argumentName) const;
	std::string const& operator[](ArgumentName const &argumentName) const;

	inline bool isHelp() const { return help; }

private:
	ArgumentMap const arguments;
	FlagMap const flags;
	ArgumentMap const shortToLongNameMap;
	bool const help;
};

}	// namespace cli
}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTS_H_INCLUDED */
