/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Error class regarding errors that occur during parsing of
 * 				a PROL16 exe file.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEPARSEERROR_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEPARSEERROR_H_INCLUDED

#include <stdexcept>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class Prol16ExeParseError final : public std::exception {
public:
	enum class ErrorType {
		MagicNumberSize,
		MagicNumberValue,
		EntryPoint,
		SymbolTableSize,
		SymbolTable,
		CodeSegment,
	};

	Prol16ExeParseError(std::string const &filename, ErrorType const errorType);

	char const* what() const noexcept override;

private:
	std::string errorMessage;
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEPARSEERROR_H_INCLUDED */
