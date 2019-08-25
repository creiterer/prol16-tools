/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "VirtualMemory.h"

#include "FileUtils.h"
#include "MathUtils.h"

#include <cstring>
#include <sstream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

VirtualMemory::Data const VirtualMemory::MagicInitValue;

VirtualMemory::VirtualMemory() {
	memory.fill(MagicInitValue);
}

void VirtualMemory::initializeFromFile(std::string const &filename) {
	using namespace util;

	FileBuffer buffer = readEntireFile(filename);
	if (!isMultiple(sizeof(Data), buffer.size())) {
		std::ostringstream errorMessage;
		errorMessage << "actual size of the file buffer (" << buffer.size() << ") ";
		errorMessage << "isn't a multiple of the data size (" << sizeof(Data) << "); ";
		errorMessage << "this indicates incomplete instructions!";
		throw std::runtime_error(errorMessage.str());
	}

	std::memcpy(memory.data(), buffer.data(), buffer.size());
	codeSegmentSize = buffer.size() / sizeof(Data);
}

} 	// namespace PROL16
