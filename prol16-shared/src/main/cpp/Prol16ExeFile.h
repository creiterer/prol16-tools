/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILE_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILE_H_INCLUDED

#include "FileUtils.h"
#include "MemoryUtils.h"

#include <array>
#include <fstream>
#include <string>
#include <vector>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

// TODO(creiterer): unit testing
class Prol16ExeFile final {
public:
	using Address = memory::Address;
	using Data = memory::Data;

	using CodeSegment = std::vector<Data>;

	static char const * const Extension;

	static unsigned const MagicNumberSize = 4;
	static std::array<unsigned char, MagicNumberSize> const MagicNumber;

	static unsigned const EntryPointAddressOffset = MagicNumberSize;
	static unsigned const CodeSegmentOffset = EntryPointAddressOffset + sizeof(Address);

	static Prol16ExeFile parse(std::string const &filename);

	inline Address getEntryPointAddress() const { return entryPointAddress; }
	inline CodeSegment getCodeSegment() const { return codeSegment; }

private:
	Address const entryPointAddress;
	CodeSegment const codeSegment;

	static void checkFileSize(::util::FileBuffer::size_type const bufferSize, std::string const &filename);
	static void checkFileStartsWithMagicNumber(::util::FileBuffer const &buffer, std::string const &filename);

	Prol16ExeFile(Address const entryPointAddress, CodeSegment codeSegment);
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILE_H_INCLUDED */
