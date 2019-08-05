/**
 * @author		creiterer
 * @date 		2019-08-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NONCOPYABLE_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NONCOPYABLE_H_INCLUDED

namespace util {

class NonCopyable {
public:
	NonCopyable() = default;
	virtual ~NonCopyable() = default;

private:
	NonCopyable(NonCopyable const &other) = delete;
	NonCopyable& operator= (NonCopyable const &other) = delete;
};

}

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_NONCOPYABLE_H_INCLUDED */
