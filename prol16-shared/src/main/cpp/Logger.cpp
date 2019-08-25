/**
 * @author		creiterer
 * @date 		2019-08-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Logger.h"

#include <algorithm>
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
