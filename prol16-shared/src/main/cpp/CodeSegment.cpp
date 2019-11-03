/**
 * @author		creiterer
 * @date 		2019-10-08
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		This class represents a PROL16 code segment.
 */

#include "CodeSegment.h"

#include "MathUtils.h"

#include <cstring>
#include <sstream>
#include <stdexcept>
#include <utility>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

CodeSegment CodeSegment::createFromFileBuffer(::util::FileBuffer const &buffer, ::util::FileBuffer::size_type const codeSegmentOffset) {
	if (!::util::isMultiple(sizeof(Data), buffer.size() - codeSegmentOffset)) {
		std::ostringstream errorMessage;
		errorMessage << "actual buffer size of the code segment (" << buffer.size() - codeSegmentOffset << ") ";
		errorMessage << "isn't a multiple of the data size (" << sizeof(Data) << "); ";
		errorMessage << "this indicates incomplete instructions!";

		throw std::runtime_error(errorMessage.str());
	}

	Segment::size_type const codeSegmentSize = (buffer.size() - codeSegmentOffset) / sizeof(Segment::value_type);

	if (codeSegmentSize == 0) {
		throw std::runtime_error("empty code segment");
	}

	Segment codeSegment(codeSegmentSize);
	std::memcpy(codeSegment.data(), buffer.data() + codeSegmentOffset, buffer.size() - codeSegmentOffset);

	return CodeSegment(codeSegment);
}

//CodeSegment CodeSegment::create(InstructionWriter::InstructionBuffer const &buffer, SymbolTable const &symbolTable) {
//	Segment codeSegment(buffer);
//
//}

CodeSegment::CodeSegment(Segment codeSegment) : codeSegment(std::move(codeSegment)) {

}

CodeSegment::CodeSegment(std::initializer_list<value_type> codeSegment) : codeSegment(codeSegment) {

}

std::string CodeSegment::readString(Address const address) const {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	return std::string(reinterpret_cast<char const*>(codeSegment.data() + address));
}

}	// namespace util
}	// namespace PROL16
