/**
 * @author		creiterer
 * @date 		2019-08-10
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NOTIMPLEMENTEDERROR_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NOTIMPLEMENTEDERROR_H_INCLUDED

#include <stdexcept>
#include <string>

#include "StringUtils.h"

namespace util {

class NotImplementedError final : public std::runtime_error {
public:
	NotImplementedError(std::string const &message) : runtime_error(prepend(message, "not implemented error: ")) {}
};

}

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NOTIMPLEMENTEDERROR_H_INCLUDED */
