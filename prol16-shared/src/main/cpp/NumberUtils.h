/**
 * @author		creiterer
 * @date 		2019-03-17
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_NUMBERUTILS_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_NUMBERUTILS_H_INCLUDED

#include <cstdint>
#include <string>
#include <ostream>

namespace PROL16 { namespace util {

using Number = uint16_t;
using Immediate = Number;

Immediate parseNumber(std::string number);

void printHexNumberFormatted(std::ostream &stream, Number const number);

}}

#endif /* PROL16_AS_SRC_MAIN_CPP_NUMBERUTILS_H_INCLUDED */
