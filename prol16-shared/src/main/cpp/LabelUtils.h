/**
 * @author		creiterer
 * @date 		2019-10-07
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_LABELUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_LABELUTILS_H_INCLUDED

#include "NumberUtils.h"

#include <string>
#include <unordered_map>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

using LabelName = std::string;
using LabelValue = util::Immediate;
using LabelTable = std::unordered_map<LabelName, LabelValue>;

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_LABELUTILS_H_INCLUDED */
