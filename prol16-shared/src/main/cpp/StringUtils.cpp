/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "StringUtils.h"

#include <algorithm>

namespace util {

std::string toLower(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

}
