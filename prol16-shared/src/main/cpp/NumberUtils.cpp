/**
 * @author		creiterer
 * @date 		2019-03-17
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "NumberUtils.h"

#include <algorithm>
#include <cctype>

namespace PROL16 { namespace util {

namespace {

int getRadix(char const suffix) {
	switch (suffix) {
	case 'b': return 2;
	case 'h': return 16;
	default: return 10;
	}
}

}

/* Number Grammar:
fragment BinaryDigit : [0-1] ;
fragment DecimalDigit : [0-9] ;
fragment HexDigit : [0-9a-fA-F] ;

fragment BinaryNumberSuffix : 'b' ;
fragment DecimalNumberSuffix : 'd' ;
fragment HexNumberSuffix : 'h' ;

fragment BinaryNumber : BinaryDigit ('_'? BinaryDigit)* BinaryNumberSuffix ;
fragment DecimalNumber : DecimalDigit ('_'? DecimalDigit)* DecimalNumberSuffix? ;
fragment HexNumber : HexDigit ('_'? HexDigit)* HexNumberSuffix ;

Number : BinaryNumber | DecimalNumber | HexNumber ;
 */

Immediate parseNumber(std::string number) {
	// remove all optional '_' characters
	auto newEnd = std::remove(number.begin(), number.end(), '_');
	number.assign(number.begin(), newEnd);

	char const suffix = number.back();

	// for decimal numbers it is allowed to omit the suffix
	// -> if the last character is not a decimal digit, it must be a suffix that needs to be removed
	if (!isdigit(suffix)) {
		number.pop_back();
	}

	return std::stoul(number, nullptr, getRadix(suffix));
}

}}
