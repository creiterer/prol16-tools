/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Error class for incomplete PROL16 instructions.
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_INCOMPLETEINSTRUCTIONERROR_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_INCOMPLETEINSTRUCTIONERROR_H_INCLUDED

#include <stdexcept>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class IncompleteInstructionError final : public std::exception {
public:
	IncompleteInstructionError();
	explicit IncompleteInstructionError(std::string const &hint);

	char const* what() const noexcept override;

private:
	std::string errorMessage;
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_INCOMPLETEINSTRUCTIONERROR_H_INCLUDED */
