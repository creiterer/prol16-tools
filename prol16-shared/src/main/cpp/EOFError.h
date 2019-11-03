/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing an end-of-file error.
 */

#ifndef PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_EOFERROR_H_INCLUDED
#define PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_EOFERROR_H_INCLUDED

#include <stdexcept>

namespace util {

class EOFError final : public std::runtime_error {
public:
	EOFError() : runtime_error("reached end-of-file") {}
};

}

#endif /* PROL16_ASM_PROL16_SHARED_SRC_MAIN_CPP_EOFERROR_H_INCLUDED */
