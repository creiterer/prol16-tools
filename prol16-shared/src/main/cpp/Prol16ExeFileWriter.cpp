/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Prol16ExeFileWriter.h"

#include "FileUtils.h"

#include <algorithm>
#include <iterator>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

char const * const Prol16ExeFileWriter::Extension{"p16"};
std::array<char, Prol16ExeFileWriter::MagicNumberSize> const Prol16ExeFileWriter::MagicNumber{0x7F, 'P', '1', '6'};

Prol16ExeFileWriter::Prol16ExeFileWriter(std::string const &filename)
: filename(filename), fileStream(filename, std::ofstream::binary) {
	if (!fileStream) {
		throw std::ios_base::failure("Failed to open PROL16 executable file '" + filename + "'");
	}
}

Prol16ExeFileWriter::~Prol16ExeFileWriter() {
	fileStream.close();
}

void Prol16ExeFileWriter::writeFileHeader(Address const entryPointAddress) {
	writeMagicNumber();
	::util::writeValueBinary(fileStream, entryPointAddress);
}

void Prol16ExeFileWriter::writeMagicNumber() {
	std::ostream_iterator<char> ostreamItor(fileStream);
	std::copy(MagicNumber.cbegin(), MagicNumber.cend(), ostreamItor);
}

}	// namespace util
}	// namespace PROL16
