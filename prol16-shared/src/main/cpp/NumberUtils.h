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

namespace PROL16 { namespace util {

using Immediate = uint16_t;

Immediate parseNumber(std::string number);

}}

#endif /* PROL16_AS_SRC_MAIN_CPP_NUMBERUTILS_H_INCLUDED */
