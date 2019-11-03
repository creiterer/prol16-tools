/**
 * @author		creiterer
 * @date 		2019-08-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class used to build an instance of CLIArguments.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTBUILDER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTBUILDER_H_INCLUDED

#include "CLIArguments.h"
#include "NonCopyable.h"

#include <string>

namespace util { namespace cli {

class CLIArgumentsBuilder final : private NonCopyable {
public:
	using ArgumentMap = CLIArguments::ArgumentMap;
	using FlagMap = CLIArguments::FlagMap;

	CLIArgumentsBuilder() = default;

	CLIArguments build() const;

	void addArgument(std::string const &name, std::string const &value);
	void addFlag(std::string const &name, bool const value);
	inline void addShortToLongNameMapping(ArgumentMap const &shortToLongNameMap) { this->shortToLongNameMap = shortToLongNameMap; }

private:
	ArgumentMap arguments;
	FlagMap flags;
	ArgumentMap shortToLongNameMap;
};

}	// namespace cli
}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTBUILDER_H_INCLUDED */
