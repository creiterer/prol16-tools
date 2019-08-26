/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Prol16ExeFileWriter.h"

#include "FileUtils.h"
#include "Prol16ExeFile.h"

#include <algorithm>
#include <iterator>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

Prol16ExeFileWriter::Prol16ExeFileWriter(std::string const &filename)
: filename(filename), fileStream(filename, std::ofstream::binary) {
	if (!fileStream) {
		throw std::ios_base::failure("Failed to open PROL16 executable file '" + filename + "'");
	}
}

Prol16ExeFileWriter::~Prol16ExeFileWriter() {
	fileStream.close();
}

void Prol16ExeFileWriter::writeFileHeader(memory::Address const entryPointAddress) {
	writeMagicNumber();
	::util::writeValueBinary(fileStream, entryPointAddress);
}

void Prol16ExeFileWriter::writeMagicNumber() {
	std::ostream_iterator<char> ostreamItor(fileStream);
	std::copy(Prol16ExeFile::MagicNumber.cbegin(), Prol16ExeFile::MagicNumber.cend(), ostreamItor);
}

}	// namespace util
}	// namespace PROL16
