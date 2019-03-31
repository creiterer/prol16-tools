/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_REGISTERERROR_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_REGISTERERROR_H_INCLUDED

#include <stdexcept>
#include <string>

#include "RegisterUtils.h"

namespace PROL16 { namespace util {

class RegisterError final : public std::exception {
public:
	RegisterError(Register const reg);
	RegisterError(std::string const &registerName);

	char const* what() const noexcept override;

private:
	std::string errorMessage;
};

}}

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_REGISTERERROR_H_INCLUDED */
