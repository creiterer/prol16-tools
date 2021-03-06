/**
 * @author		creiterer
 * @date 		2019-08-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		A logger class for convenient logging to different log streams.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_LOGGER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_LOGGER_H_INCLUDED

#include "NonCopyable.h"

#include <functional>
#include <initializer_list>
#include <ios>
#include <ostream>
#include <string>
#include <vector>

namespace util { namespace logging {

class Logger final : private NonCopyable {
public:
	// since pure references are not assignable, they cannot be used as element type for vectors -> use std::reference_wrapper
	// see https://stackoverflow.com/questions/23488326/stdvector-of-references/23488449
	// see https://stackoverflow.com/questions/922360/why-cant-i-make-a-vector-of-references
	using LogStream = std::ostream&;
	using LogStreams = std::vector<std::reference_wrapper<std::ostream>>;

	enum class Adjustment {
		Left,
		Right,
		Internal,
	};

	explicit Logger(LogStream logStream, bool const enabled = true);
	explicit Logger(LogStreams const &logStreams, bool const enabled = true);
	explicit Logger(LogStreams &&logStreams, bool const enabled = true);
	Logger(std::initializer_list<std::reference_wrapper<std::ostream>> logStreams, bool const enabled = true);

	inline void addLogStream(LogStream logStream) { logStreams.emplace_back(logStream); }

	inline void setEnabled(bool const enabled) { this->enabled = enabled; }
	inline bool isEnabled() const { return enabled; }
	inline void enable() { enabled = true; }
	inline void disable() { enabled = false; }

	void forEachLogStream(std::function<void(LogStream)> const &function);
	LogStreams& ifDisabledLogTo(LogStreams &logStreams);

	std::streamsize setWidth(std::streamsize const width);
	void restoreWidth();

	char setFillCharacter(char const fillCharacter);
	void restoreFillCharacter();

	void setAdjustment(Adjustment const adjustment);
	void restoreAdjustment();

	void setFormat(std::streamsize const width, char const fillCharacter);
	void setFormat(std::streamsize const width, char const fillCharacter, Adjustment const adjustment);
	void restoreFormat();

	void logTimestamp(std::string const &prefix = "", std::string const &suffix = "");

	template <typename T>
	Logger& operator<<(T const &value) {
		if (enabled) {
			for (LogStream logStream : logStreams) {
				logStream << value;
			}
		}

		return *this;
	}

	// https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt
//	Logger& operator<<(short const value);
//	Logger& operator<<(unsigned short const value);
//	Logger& operator<<(int const value);
//	Logger& operator<<(unsigned int const value);
//	Logger& operator<<(long const value);
//	Logger& operator<<(unsigned long const value);
//	Logger& operator<<(long long const value);
//	Logger& operator<<(unsigned long long const value);
//	Logger& operator<<(float const value);
//	Logger& operator<<(double const value);
//	Logger& operator<<(long double const value);
//	Logger& operator<<(bool const value);
//	Logger& operator<<(void const * const value);

private:
	LogStreams logStreams;
	bool enabled;
	std::streamsize oldWidth{0};
	char oldFillCharacter{' '};
	Adjustment oldAdjustment{Adjustment::Right};

	void setAdjustmentAux(Adjustment const adjustment);
};

}	// namespace logging
}	// namespace util

template <typename T>
::util::logging::Logger::LogStreams& operator<<(::util::logging::Logger::LogStreams &logStreams, T const &value) {
	for (::util::logging::Logger::LogStream logStream : logStreams) {
		logStream << value;
	}

	return logStreams;
}

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_LOGGER_H_INCLUDED */
