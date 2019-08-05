/**
 * @author		creiterer
 * @date 		2019-08-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NONCONSTRUCTABLE_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NONCONSTRUCTABLE_H_INCLUDED

#include "NonCopyable.h"

namespace util {

class NonConstructable : private NonCopyable {
private:
	NonConstructable() = delete;
};

}

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NONCONSTRUCTABLE_H_INCLUDED */
