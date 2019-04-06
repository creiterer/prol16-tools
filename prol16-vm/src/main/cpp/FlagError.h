/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_FLAGERROR_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_FLAGERROR_H_INCLUDED

#include <stdexcept>

namespace PROL16 { namespace util {

class FlagError final : public std::runtime_error {
public:
	FlagError(std::string const &name) : runtime_error(name + " has an undefined value") {}
};

}}

#endif /* PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_FLAGERROR_H_INCLUDED */
