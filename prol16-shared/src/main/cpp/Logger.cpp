/**
 * @author		creiterer
 * @date 		2019-08-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Logger.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <stdexcept>
#include <utility>

namespace util { namespace logging {

Logger::Logger(LogStream logStream, bool const enabled) : logStreams{logStream}, enabled(enabled) {}

// NOLINTNEXTLINE(modernize-pass-by-value): makes no sense since there is an explicit rvalue-ref overload
Logger::Logger(LogStreams const &logStreams, bool const enabled) : logStreams(logStreams), enabled(enabled) {}

Logger::Logger(LogStreams &&logStreams, bool const enabled) : logStreams(std::move(logStreams)), enabled(enabled) {}

Logger::Logger(std::initializer_list<std::reference_wrapper<std::ostream>> logStreams, bool const enabled) : logStreams(logStreams), enabled(enabled) {}

void Logger::forEachLogStream(std::function<void(LogStream)> const &function) {
	if (enabled) {
		std::for_each(logStreams.begin(), logStreams.end(), function);
	}
}

Logger::LogStreams& Logger::ifDisabledLogTo(LogStreams &logStreams) {
	if (enabled) {
		return this->logStreams;
	}

	return logStreams;
}

std::streamsize Logger::setWidth(std::streamsize const width) {
	oldWidth = logStreams.front().get().width();

	forEachLogStream([width](LogStream stream){
		stream.width(width);
	});

	return oldWidth;
}

void Logger::restoreWidth() {
	forEachLogStream([this](LogStream stream){
		stream.width(oldWidth);
	});
}

char Logger::setFillCharacter(char const fillCharacter) {
	oldFillCharacter = logStreams.front().get().fill();

	forEachLogStream([fillCharacter](LogStream stream){
		stream.fill(fillCharacter);
	});

	return oldFillCharacter;
}

void Logger::restoreFillCharacter() {
	forEachLogStream([this](LogStream stream){
		stream.fill(oldFillCharacter);
	});
}

void Logger::setAdjustment(Adjustment const adjustment) {
	std::ios_base::fmtflags formatFlags = logStreams.front().get().flags();
	if ((formatFlags & std::ios_base::left) != 0) {
		oldAdjustment = Adjustment::Left;
	} else if ((formatFlags & std::ios_base::right) != 0) {
		oldAdjustment = Adjustment::Right;
	} else {
		oldAdjustment = Adjustment::Internal;
	}

	setAdjustmentAux(adjustment);
}

void Logger::restoreAdjustment() {
	setAdjustmentAux(oldAdjustment);
}

void Logger::setFormat(std::streamsize const width, char const fillCharacter) {
	setWidth(width);
	setFillCharacter(fillCharacter);
}

void Logger::setFormat(std::streamsize const width, char const fillCharacter, Adjustment const adjustment) {
	setWidth(width);
	setFillCharacter(fillCharacter);
	setAdjustment(adjustment);
}

void Logger::restoreFormat() {
	restoreWidth();
	restoreFillCharacter();
	restoreAdjustment();
}

void Logger::logTimestamp(std::string const &prefix, std::string const &suffix) {
	using namespace std::chrono;

	time_t timeInfo = system_clock::to_time_t(system_clock::now());
	logStreams << prefix << ctime(&timeInfo) << suffix;
}

void Logger::setAdjustmentAux(Adjustment const adjustment) {
	forEachLogStream([adjustment](LogStream stream){
		switch (adjustment) {
		case Adjustment::Left:
			stream << std::left;
			break;
		case Adjustment::Right:
			stream << std::right;
			break;
		case Adjustment::Internal:
			stream << std::internal;
			break;
		default:
			throw std::logic_error("Logger: trying to set invalid adjustment");
		}
	});
}

/*
Logger& Logger::operator<<(short const value) {

}

Logger& Logger::operator<<(unsigned short const value) {

}

Logger& Logger::operator<<(int const value) {

}

Logger& Logger::operator<<(unsigned int const value) {

}

Logger& Logger::operator<<(long const value) {

}
Logger& Logger::operator<<(unsigned long const value) {

}

Logger& Logger::operator<<(long long const value) {

}

Logger& Logger::operator<<(unsigned long long const value) {

}

Logger& Logger::operator<<(float const value) {

}

Logger& Logger::operator<<(double const value) {

}

Logger& Logger::operator<<(long double const value) {

}

Logger& Logger::operator<<(bool const value) {

}

Logger& Logger::operator<<(void const * const value) {

}
*/

}	// namespace logging
}	// namespace util
