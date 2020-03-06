/**
 * @author		creiterer
 * @date 		2019-10-08
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		This class represents a PROL16 code segment.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CODESEGMENT_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CODESEGMENT_H_INCLUDED

#include "FileUtils.h"
#include "InstructionWriter.h"
#include "MemoryUtils.h"
#include "SymbolTable.h"

#include <initializer_list>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class CodeSegment final {
public:
	using Address = memory::Address;
	using Data = memory::Data;
	using Segment = memory::Segment;

	using value_type = Segment::value_type;
	using size_type = Segment::size_type;
	using const_iterator = Segment::const_iterator;
	using const_reference = Segment::const_reference;

	static CodeSegment createFromFileBuffer(::util::FileBuffer const &buffer, ::util::FileBuffer::size_type const codeSegmentOffset);
//	static CodeSegment create(InstructionWriter::InstructionBuffer const &buffer, SymbolTable const &symbolTable);

	explicit CodeSegment(Segment codeSegment);
	CodeSegment(std::initializer_list<value_type> codeSegment);

	inline size_type size() const noexcept { return codeSegment.size(); }

	inline const_reference at(Address const address) const { return codeSegment.at(address); }

	inline const_iterator begin() const noexcept { return codeSegment.begin(); }
	inline const_iterator cbegin() const noexcept { return codeSegment.cbegin(); }

	inline const_iterator end() const noexcept { return codeSegment.end(); }
	inline const_iterator cend() const noexcept { return codeSegment.cend(); }

	inline bool isAddressValid(Address const address) const noexcept { return address < size(); }

	std::string readString(Address const address) const;

private:
	Segment const codeSegment;
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_CODESEGMENT_H_INCLUDED */
