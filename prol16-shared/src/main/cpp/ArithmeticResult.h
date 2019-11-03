/**
 * @author		creiterer
 * @date 		2019-10-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing the result of a PROL16 arithmetic operation.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARITHMETICRESULT_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARITHMETICRESULT_H_INCLUDED

#include <cstdint>
#include <type_traits>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class ArithmeticResult final {
public:
	using ResultType = uint32_t;
	using LowHighType = uint16_t;

	// NOLINTNEXTLINE(google-explicit-constructor)
	ArithmeticResult(ResultType const result);

	ArithmeticResult& operator=(ResultType const result);

	inline void set(ResultType const result) { this->result = result; }
	inline ResultType get() const { return result; }

	// NOLINTNEXTLINE(google-explicit-constructor)
	inline operator ResultType() { return get(); }

	LowHighType getLow() const;
	LowHighType getHigh() const;

	bool isOverflow(unsigned const bitWidth) const;

private:
	ResultType result;
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_ARITHMETICRESULT_H_INCLUDED */
