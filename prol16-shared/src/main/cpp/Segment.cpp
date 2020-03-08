/**
 * @author		creiterer
 * @date 		2019-10-08
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		This class represents a PROL16 segment.
 */

#include "Segment.h"

#include "MathUtils.h"

#include <cstring>
#include <sstream>
#include <stdexcept>
#include <utility>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

Segment Segment::createFromFileBuffer(::util::FileBuffer const &buffer, ::util::FileBuffer::size_type const segmentOffset, size_type const segmentSize) {
	if (segmentSize != 0 && !::util::isMultiple(sizeof(Data), buffer.size() - segmentOffset)) {
		std::ostringstream errorMessage;
		errorMessage << "actual buffer size of the segment (" << buffer.size() - segmentOffset << ") ";
		errorMessage << "isn't a multiple of the data size (" << sizeof(Data) << "); ";
		errorMessage << "this indicates incomplete instructions!";

		throw std::runtime_error(errorMessage.str());
	}

	MemorySegment segment(segmentSize);
	std::memcpy(segment.data(), buffer.data() + segmentOffset, segmentSize * sizeof(Data));

	return Segment(std::move(segment));
}

Segment::Segment(MemorySegment segment) : segment(std::move(segment)) {

}

Segment::Segment(std::initializer_list<value_type> segment) : segment(segment) {

}

std::string Segment::readString(Address const address) const {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	return std::string(reinterpret_cast<char const*>(segment.data() + address));
}

}	// namespace util
}	// namespace PROL16
