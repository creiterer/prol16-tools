/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "FileUtils.h"

#include "ScopedFileStream.h"
#include "StringUtils.h"

#include <cassert>
#include <sstream>
#include <stdexcept>

namespace util {

FileSize getFileSize(std::ifstream &stream) {
	stream.seekg(0, std::istream::end);
	FileSize const fileSize = stream.tellg();
	stream.seekg(0, std::istream::beg);

	return fileSize;
}

FileBuffer readEntireFile(std::string const &filename) {
	ScopedFileStream<std::ifstream> inputFileStream(filename, std::ifstream::binary);

	return readEntireStream(inputFileStream);
}

FileBuffer readEntireStream(util::ScopedFileStream<std::ifstream> &stream) {
	return readEntireStream(stream.stream(), stream.getFilename());
}

FileBuffer readEntireStream(std::ifstream &stream, std::string const &filename) {
	FileSize const fileSize = getFileSize(stream);
	FileBuffer buffer(fileSize);

	// reserve() doesn't work because using data() to write data into the vector doesn't update its size appropriately
	// -> need to ensure the correct size before -> use the fill constructor or the resize() method!
	//buffer.reserve(fileLength);

	// reinterpret_cast is necessary in this case
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	stream.read(reinterpret_cast<char*>(buffer.data()), fileSize);

	if ((!stream) || (stream.gcount() != static_cast<std::streamsize>(fileSize))) {
		std::ostringstream errorMessage;
		errorMessage << "failed to read the entire file '" << filename << "'; ";
		errorMessage << "only " << stream.gcount() << " of " << fileSize << " bytes were read successfully";

		throw std::runtime_error(errorMessage.str());
	}

	assert(buffer.size() == fileSize);

	return buffer;
}

std::string getBufferAsString(FileBuffer const &buffer) {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	return std::string(reinterpret_cast<char const*>(buffer.data()), buffer.size());
}

char const* getBufferAsCString(FileBuffer const &buffer, FileBuffer::size_type const offset) {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	return reinterpret_cast<char const*>(buffer.data() + offset);
}

void writeStringToStream(std::ostream &stream, std::string const &str) {
	stream.write(str.c_str(), str.length() + 1);	// +1 for terminating null character
}

void writeStringPaddedToStream(std::ostream &stream, std::string str, unsigned const alignment) {
	pad(str, alignment);
	writeStringToStream(stream, str);
}

} 	// namespace util
