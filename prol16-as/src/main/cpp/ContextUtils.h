/**
 * @author		creiterer
 * @date 		2019-08-10
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_AS_SRC_MAIN_CPP_CONTEXTUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_AS_SRC_MAIN_CPP_CONTEXTUTILS_H_INCLUDED

#include "Prol16AsmParserBaseListener.h"

namespace PROL16 { namespace util {

bool isNumber(Prol16AsmParser::ExpressionContext const * const expression);
bool isIdentifier(Prol16AsmParser::ExpressionContext const * const expression);
bool isRegister(Prol16AsmParser::PrintInstructionContext const * const context);
bool isImmediate(Prol16AsmParser::PrintInstructionContext const * const context);
bool isString(Prol16AsmParser::PrintInstructionContext const * const context);

}}

#endif /* PROL16_TOOLS_PROL16_AS_SRC_MAIN_CPP_CONTEXTUTILS_H_INCLUDED */