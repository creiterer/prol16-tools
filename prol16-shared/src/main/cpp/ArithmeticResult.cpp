/**
 * @author		creiterer
 * @date 		2019-10-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "ArithmeticResult.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

ArithmeticResult::ArithmeticResult(ResultType const result) : result(result) {

}

ArithmeticResult& ArithmeticResult::operator=(ResultType const result) {
	this->result = result;

	return *this;
}

ArithmeticResult::LowHighType ArithmeticResult::getLow() const {
	return static_cast<LowHighType>(result);
}

ArithmeticResult::LowHighType ArithmeticResult::getHigh() const {
	return static_cast<LowHighType>(result >> (sizeof(LowHighType) * 8));
}

bool ArithmeticResult::isOverflow(unsigned const bitWidth) const {
	return (result >> bitWidth) != 0;
}

}	// namespace util
}	// namespace PROL16
