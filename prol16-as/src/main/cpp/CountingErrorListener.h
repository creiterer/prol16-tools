/**
 * @author		creiterer
 * @date 		2019-03-30
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Error listener that counts the number of errors.
 */

#ifndef PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_COUNTINGERRORLISTENER_H_INCLUDED
#define PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_COUNTINGERRORLISTENER_H_INCLUDED

#include "BaseErrorListener.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class CountingErrorListener final : public antlr4::BaseErrorListener {
public:
	CountingErrorListener() = default;

	void syntaxError(antlr4::Recognizer */*recognizer*/, antlr4::Token */*offendingSymbol*/, size_t /*line*/, size_t /*charPositionInLine*/,
					 const std::string &/*msg*/, std::exception_ptr /*e*/) override {
		++errorCount;
	}

	inline unsigned getErrorCount() const { return errorCount; }

	inline bool hasFoundErrors() const { return errorCount != 0; }

private:
	unsigned errorCount = 0;
};

} 	// namespace PROL16

#endif /* PROL16_ASM_PROL16_AS_SRC_MAIN_CPP_COUNTINGERRORLISTENER_H_INCLUDED */
