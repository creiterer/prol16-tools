/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "FileUtils.h"

#include <stdexcept>
#include <sstream>

#include "ScopedFileStream.h"

namespace util {

std::streampos getFileLength(std::ifstream &stream) {
	stream.seekg (0, stream.end);
	std::streampos const fileLength = stream.tellg();
	stream.seekg (0, stream.beg);

	return fileLength;
}

FileBuffer readEntireFile(std::string const &filename) {
	ScopedFileStream<std::ifstream> inputFileStream(filename, std::ifstream::binary);

	std::streampos const fileLength = getFileLength(inputFileStream);
	FileBuffer buffer(fileLength);

	// reserve() doesn't work because using data() to write data into the vector doesn't update its size appropriately
	// -> need to ensure the correct size before -> use the fill constructor or the resize() method!
	//buffer.reserve(fileLength);

	inputFileStream.stream().read(reinterpret_cast<char*>(buffer.data()), fileLength);

	if ((!inputFileStream.stream()) || (inputFileStream.stream().gcount() != fileLength)) {
		std::ostringstream errorMessage;
		errorMessage << "failed to read the entire file '" << filename << "'; ";
		errorMessage << "only " << inputFileStream.stream().gcount() << " of " << fileLength << " bytes were read successfully";

		throw std::runtime_error(errorMessage.str());
	}

	return buffer;
}

}