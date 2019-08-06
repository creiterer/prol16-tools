/**
 * @author		creiterer
 * @date 		2019-08-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIFLAGS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIFLAGS_H_INCLUDED

#include <string>

namespace util { namespace cli { namespace flags {

struct FlagName final {
	std::string const shortName;
	std::string const longName;
};

static FlagName const VERBOSE{"-v", "--verbose"};

}}}

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CLIFLAGS_H_INCLUDED */
