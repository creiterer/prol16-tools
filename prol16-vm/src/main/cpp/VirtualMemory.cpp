/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing the PROL16 memory.
 */

#include "VirtualMemory.h"

#include "FileUtils.h"
#include "MathUtils.h"

#include <algorithm>
#include <cstring>
#include <iterator>
#include <sstream>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

VirtualMemory::Data const VirtualMemory::MagicInitValue;

VirtualMemory::VirtualMemory() {
	memory.fill(MagicInitValue);
}

std::string VirtualMemory::readString(Address const address) const {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	return std::string(reinterpret_cast<char const*>(memory.data() + address));
}

VirtualMemory::MemoryRange VirtualMemory::readRange(Address const startAddress, Address const endAddress) const {
	if (!(startAddress < size())) {
		throw std::out_of_range("start address is out of valid memory range");
	}
	if (!(endAddress < size())) {
		throw std::out_of_range("end address is out of valid memory range");
	}

	return MemoryRange(std::next(memory.cbegin(), startAddress), std::next(memory.cbegin(), endAddress + 1));
}

void VirtualMemory::initializeFromFile(std::string const &filename) {
	::util::FileBuffer buffer = ::util::readEntireFile(filename);
	if (!::util::isMultiple(sizeof(Data), buffer.size())) {
		std::ostringstream errorMessage;
		errorMessage << "actual size of the file buffer (" << buffer.size() << ") ";
		errorMessage << "isn't a multiple of the data size (" << sizeof(Data) << "); ";
		errorMessage << "this indicates incomplete instructions!";

		throw std::runtime_error(errorMessage.str());
	}

	std::memcpy(memory.data(), buffer.data(), buffer.size());
	codeSegmentSize = buffer.size() / sizeof(Data);
}

void VirtualMemory::initializeCodeSegment(util::CodeSegment const &codeSegment) {
	if (codeSegment.size() > MaxCodeSegmentSize) {
		throw std::runtime_error("code segment from file doesn't fit into code segment from memory");
	}

	std::copy(codeSegment.cbegin(), codeSegment.cend(), std::next(memory.begin(), CodeSegmentOffset));
	codeSegmentSize = codeSegment.size();
}

} 	// namespace PROL16
