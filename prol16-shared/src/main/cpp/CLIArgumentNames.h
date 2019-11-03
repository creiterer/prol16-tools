/**
 * @author		creiterer
 * @date 		2019-08-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		This file contains some standard (i.e. used across all prol16 tools)
 * 				CLI argument names for options and flags.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTNAMES_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTNAMES_H_INCLUDED

#include <string>

namespace util { namespace cli {

struct ArgumentName final {
	std::string const shortName;
	std::string const longName;
};

namespace flags {

static ArgumentName const HELP{"-h", "--help"};
static ArgumentName const INTERACTIVE{"-i", "--interactive"};
static ArgumentName const VERBOSE{"-v", "--verbose"};

}	// namespace flags

namespace options {

static ArgumentName const LOGFILE{"-l", "--log-file"};

}	// namespace options


}	// namespace cli
}	// namespace util

bool operator==(std::string const &lhs, ::util::cli::ArgumentName const &rhs);
bool operator==(::util::cli::ArgumentName const &lhs, std::string const &rhs);

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTNAMES_H_INCLUDED */
