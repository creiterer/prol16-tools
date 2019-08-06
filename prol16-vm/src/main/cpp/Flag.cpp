/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Flag.h"

#include "FlagError.h"

namespace PROL16 {

Flag::Flag(std::string const &flagName) : state(State::Undefined), name(flagName) {

}

void Flag::set(bool const value) {
	if (value) {
		state = State::One;
	} else {
		state = State::Zero;
	}
}

bool Flag::isSet() const {
	checkFlagIsValid();

	return state == State::One;
}

std::string Flag::asString() const {
	switch (state) {
	case Flag::State::Undefined:
		return "undefined";
	case Flag::State::Zero:
		return "0";
	case Flag::State::One:
		return "1";
	default:
		return "internal error";
	}
}

void Flag::checkFlagIsValid() const {
	if (state == State::Undefined) {
		throw util::FlagError(name);
	}
}

}

util::logging::Logger& operator<<(util::logging::Logger &logger, PROL16::Flag const &flag) {
	logger << flag.asString();
	return logger;
}
