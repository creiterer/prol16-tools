/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing a PROL16 flag (e.g. carry flag and zero flag).
 */

#include "Flag.h"

#include "FlagError.h"

#include <utility>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

Flag::Flag(std::string flagName) : state(State::Undefined), name(std::move(flagName)) {

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
		return "?";
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

} 	// namespace PROL16

std::ostream& operator<<(std::ostream &stream, PROL16::Flag const &flag) {
	stream << flag.asString();
	return stream;
}

util::logging::Logger& operator<<(util::logging::Logger &logger, PROL16::Flag const &flag) {
	logger << flag.asString();
	return logger;
}
