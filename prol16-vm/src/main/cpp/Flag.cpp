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

void Flag::checkFlagIsValid() const {
	if (state == State::Undefined) {
		throw util::FlagError(name);
	}
}

}

