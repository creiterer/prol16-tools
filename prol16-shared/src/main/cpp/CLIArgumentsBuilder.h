/**
 * @author		creiterer
 * @date 		2019-08-04
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTBUILDER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTBUILDER_H_INCLUDED

#include <string>

#include "NonCopyable.h"
#include "CLIArguments.h"

namespace util {

class CLIArgumentsBuilder final : private NonCopyable {
public:
	using ArgumentMap = CLIArguments::ArgumentMap;
	using FlagMap = CLIArguments::FlagMap;

	CLIArgumentsBuilder() = default;
	~CLIArgumentsBuilder() = default;

	CLIArguments build() const;

	void addArgument(std::string const &name, std::string const &value);
	void addFlag(std::string const &name, bool const value);
	inline void addShortToLongNameMapping(ArgumentMap const &shortToLongNameMap) { this->shortToLongNameMap = shortToLongNameMap; }

private:
	ArgumentMap arguments;
	FlagMap flags;
	ArgumentMap shortToLongNameMap;
};

}

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTBUILDER_H_INCLUDED */
