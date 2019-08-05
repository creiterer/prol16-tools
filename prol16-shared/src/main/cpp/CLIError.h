/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_CLIERROR_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_CLIERROR_H_INCLUDED

#include <stdexcept>
#include <string>

namespace util {

class CLIError final : public std::runtime_error {
public:
	CLIError(std::string const &message) : runtime_error(message) {}
	CLIError(std::string const &error, std::string const &usage) : runtime_error(error + "\n" + usage) {}
};

}

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_CLIERROR_H_INCLUDED */
