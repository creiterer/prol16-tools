/**
 * @author		creiterer
 * @date 		2019-10-08
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		This class represents a PROL16 segment.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SEGMENT_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SEGMENT_H_INCLUDED

#include "FileUtils.h"
#include "InstructionWriter.h"
#include "MemoryUtils.h"
#include "SymbolTable.h"

#include <initializer_list>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class Segment final {
public:
	using Address = memory::Address;
	using Data = memory::Data;
	using MemorySegment = memory::Segment;

	using value_type = MemorySegment::value_type;
	using size_type = MemorySegment::size_type;
	using const_iterator = MemorySegment::const_iterator;
	using const_reference = MemorySegment::const_reference;

	static Segment createFromFileBuffer(::util::FileBuffer const &buffer, ::util::FileBuffer::size_type const segmentOffset, size_type const segmentSize);
//	static CodeSegment create(InstructionWriter::InstructionBuffer const &buffer, SymbolTable const &symbolTable);

	explicit Segment(MemorySegment segment);
	Segment(std::initializer_list<value_type> segment);

	inline size_type size() const noexcept { return segment.size(); }

	inline const_reference at(Address const address) const { return segment.at(address); }

	inline const_iterator begin() const noexcept { return segment.begin(); }
	inline const_iterator cbegin() const noexcept { return segment.cbegin(); }

	inline const_iterator end() const noexcept { return segment.end(); }
	inline const_iterator cend() const noexcept { return segment.cend(); }

	inline bool isAddressValid(Address const address) const noexcept { return address < size(); }

	std::string readString(Address const address) const;

private:
	MemorySegment const segment;
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SEGMENT_H_INCLUDED */
