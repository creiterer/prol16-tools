/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Prol16ExeFile.h"

#include "FileUtils.h"

#include <algorithm>
#include <iterator>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

char const * const Prol16ExeFile::Extension{"p16"};
std::array<char, Prol16ExeFile::MagicNumberSize> const Prol16ExeFile::MagicNumber{0x7F, 'P', '1', '6'};

Prol16ExeFile::Prol16ExeFile(std::string const &filename)
: filename(filename), fileStream(filename, std::ofstream::binary) {
	if (!fileStream) {
		throw std::ios_base::failure("Failed to open PROL16 executable file '" + filename + "'");
	}
}

Prol16ExeFile::~Prol16ExeFile() {
	fileStream.close();
}

void Prol16ExeFile::writeFileHeader(Address const entryPointAddress) {
	writeMagicNumber();
	::util::writeValueBinary(fileStream, entryPointAddress);
}

void Prol16ExeFile::writeMagicNumber() {
	std::ostream_iterator<char> ostreamItor(fileStream);
	std::copy(MagicNumber.cbegin(), MagicNumber.cend(), ostreamItor);
}

}	// namespace util
}	// namespace PROL16
