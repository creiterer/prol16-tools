/**
 * @author		creiterer
 * @date 		2019-03-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_REGISTERERROR_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_REGISTERERROR_H_INCLUDED

#include "RegisterUtils.h"

#include <stdexcept>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class RegisterError final : public std::exception {
public:
	explicit RegisterError(Register const reg);
	explicit RegisterError(std::string const &registerName);

	char const* what() const noexcept override;

private:
	std::string errorMessage;
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_REGISTERERROR_H_INCLUDED */
