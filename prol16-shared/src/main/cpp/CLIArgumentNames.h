/**
 * @author		creiterer
 * @date 		2019-08-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
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

static ArgumentName const INTERACTIVE{"-i", "--interactive"};
static ArgumentName const VERBOSE{"-v", "--verbose"};

}	// namespace flags

namespace options {

static ArgumentName const LOGFILE{"-l", "--log-file"};

}	// namespace options


}	// namespace cli
}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIARGUMENTNAMES_H_INCLUDED */
