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

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

using Number = uint16_t;
using Immediate = Number;

static int const BinaryBase = 2;
static int const DecimalBase = 10;
static int const HexBase = 16;

Number parseNumber(std::string number);

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_AS_SRC_MAIN_CPP_NUMBERUTILS_H_INCLUDED */
