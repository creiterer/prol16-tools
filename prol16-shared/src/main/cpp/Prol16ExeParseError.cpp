/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Prol16ExeParseError.h"

#include <sstream>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

Prol16ExeParseError::Prol16ExeParseError(std::string const &filename, ErrorType const errorType) {
	std::ostringstream errorMessageStream;

	errorMessageStream << "PROL16 executable file '" << filename << "' ";

	switch (errorType) {
	case ErrorType::MagicNumberSize:
	case ErrorType::MagicNumberValue:
		errorMessageStream << "does not start with the correct magic number";
		break;
	case ErrorType::EntryPoint:
		errorMessageStream << "does not contain a valid entry point address";
		break;
	case ErrorType::SymbolTableSize:
		errorMessageStream << "does not contain the size of the symbol table";
		break;
	case ErrorType::SymbolTable:
		errorMessageStream << "does not contain a valid symbol table";
		break;
	case ErrorType::CodeSegment:
		errorMessageStream << "does not contain a valid code segment";
		break;
	default:
		errorMessageStream << ": unknown error!";
		break;
	}

	errorMessage = errorMessageStream.str();
}

char const* Prol16ExeParseError::what() const noexcept {
	return errorMessage.c_str();
}

}	// namespace util
}	// namespace PROL16
