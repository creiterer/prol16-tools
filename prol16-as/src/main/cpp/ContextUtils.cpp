/**
 * @author		creiterer
 * @date 		2019-08-10
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "ContextUtils.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

bool isNumber(Prol16AsmParser::ExpressionContext const * const expression) {
	return expression->number != nullptr;
}

bool isIdentifier(Prol16AsmParser::ExpressionContext const * const expression) {
	return expression->identifier != nullptr;
}

bool isRegister(Prol16AsmParser::PrintInstructionContext const * const context) {
	return context->ra != nullptr;
}

bool isImmediate(Prol16AsmParser::PrintInstructionContext const * const context) {
	return context->immediate != nullptr;
}

bool isString(Prol16AsmParser::PrintInstructionContext const * const context) {
	return context->string != nullptr;
}

bool isNumber(Prol16AsmParser::DataWordStoreContext const * const context) {
	return context->number != nullptr;
}

bool isString(Prol16AsmParser::DataWordStoreContext const * const context) {
	return context->string != nullptr;
}

}	// namespace util
}	// namespace PROL16
