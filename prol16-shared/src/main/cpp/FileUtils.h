/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Various utility functions for different file operations.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FILEUTILS_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FILEUTILS_H_INCLUDED

#include "ScopedFileStream.h"

#include <fstream>
#include <string>
#include <type_traits>
#include <vector>

namespace util {

template <typename T>
using Buffer = std::vector<T>;

using FileBuffer = Buffer<unsigned char>;
using FileSize = FileBuffer::size_type;

FileSize getFileSize(std::ifstream const &stream);

FileBuffer readEntireFile(std::string const &filename);
FileBuffer readEntireStream(util::ScopedFileStream<std::ifstream> &stream);
FileBuffer readEntireStream(std::ifstream &stream, std::string const &filename = "");

std::string getBufferAsString(FileBuffer const &buffer);
char const* getBufferAsCString(FileBuffer const &buffer, FileBuffer::size_type const offset = 0);

void writeStringToStream(std::ostream &stream, std::string const &str);
void writeStringPaddedToStream(std::ostream &stream, std::string str, unsigned const alignment);

template <typename T>
void writeValueBinary(std::ostream &stream, T value) {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	stream.write(reinterpret_cast<char*>(&value), sizeof(T)/sizeof(char));
}

template <typename T>
T readValue(FileBuffer const &buffer, FileBuffer::size_type const offset = 0) {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	return *reinterpret_cast<T const*>(buffer.data() + offset);
}

template <typename T>
void writeBufferToStream(std::ostream &stream, Buffer<T> const &buffer) {
	static_assert(std::is_integral<T>::value, "writeBufferToStream() requires an integral value type for the buffer.");

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	stream.write(reinterpret_cast<char const*>(buffer.data()), buffer.size()*(sizeof(T)/sizeof(char)));
}

}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_FILEUTILS_H_INCLUDED */
