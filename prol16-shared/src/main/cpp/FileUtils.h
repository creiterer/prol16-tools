/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FILEUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FILEUTILS_H_INCLUDED

#include <fstream>
#include <vector>

namespace util {

using FileBuffer = std::vector<unsigned char>;

std::streampos getFileLength(std::ifstream const &stream);

FileBuffer readEntireFile(std::string const &filename);

template <typename T>
void writeValueBinary(std::ostream &stream, T value) {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	stream.write(reinterpret_cast<char*>(&value), sizeof(T)/sizeof(char));
}

}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FILEUTILS_H_INCLUDED */
