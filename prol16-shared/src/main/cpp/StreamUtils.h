/**
 * @author		creiterer
 * @date 		2019-12-03
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utilities for stream operations.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_STREAMUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_STREAMUTILS_H_INCLUDED

#include <ostream>
#include <vector>

// no namespace decl so that operator<< is in the global namespace

template <typename T>
std::ostream& operator<<(std::ostream &stream, std::vector<T> const &container) {
	stream << '{';

	if (!container.empty()) {
		stream << container.at(0);
	}

	for (size_t i = 1; i < container.size(); ++i) {
		stream << ", " << container.at(i);
	}

	stream << '}';

	return stream;
}

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_STREAMUTILS_H_INCLUDED */
