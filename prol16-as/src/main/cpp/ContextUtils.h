/**
 * @author		creiterer
 * @date 		2019-08-10
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utility functions for various Prol16AsmParser context types.
 */

#ifndef PROL16_TOOLS_PROL16_AS_SRC_MAIN_CPP_CONTEXTUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_AS_SRC_MAIN_CPP_CONTEXTUTILS_H_INCLUDED

#include "Prol16AsmParserBaseListener.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

bool isNumber(Prol16AsmParser::ExpressionContext const * const expression);
bool isIdentifier(Prol16AsmParser::ExpressionContext const * const expression);

bool isNumber(Prol16AsmParser::DataWordStoreContext const * const context);
bool isString(Prol16AsmParser::DataWordStoreContext const * const context);
}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_AS_SRC_MAIN_CPP_CONTEXTUTILS_H_INCLUDED */
