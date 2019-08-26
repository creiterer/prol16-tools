/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_FLAG_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_FLAG_H_INCLUDED

#include "Logger.h"

#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class Flag final {
public:
	explicit Flag(std::string flagName);

	explicit operator bool() const { return isSet(); }

	inline void reset() { state = State::Zero; }
	void set(bool const value = true);

	bool isSet() const;

	std::string asString() const;

private:
	enum class State {
		Zero,
		One,
		Undefined,
	};

	State state;
	std::string const name;

	void checkFlagIsValid() const;
};

}	// namespace PROL16

std::ostream& operator<<(std::ostream &stream, PROL16::Flag const &flag);
util::logging::Logger& operator<<(util::logging::Logger &logger, PROL16::Flag const &flag);

#endif /* PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_FLAG_H_INCLUDED */
