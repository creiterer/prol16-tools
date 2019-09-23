/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Prol16ExeFile.h"

#include "FileUtils.h"
#include "MathUtils.h"
#include "Prol16ExeParseError.h"

#include <algorithm>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <utility>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

char const * const Prol16ExeFile::Extension{"p16"};
std::array<unsigned char, Prol16ExeFile::MagicNumberSize> const Prol16ExeFile::MagicNumber{0x7F, 'P', '1', '6'};

Prol16ExeFile Prol16ExeFile::parse(std::string const &filename) {
	return parse(::util::readEntireFile(filename), filename);
}

Prol16ExeFile Prol16ExeFile::parse(::util::ScopedFileStream<std::ifstream> &sourceStream) {
	return parse(::util::readEntireStream(sourceStream), sourceStream.getFilename());
}

Prol16ExeFile Prol16ExeFile::parse(std::ifstream &sourceStream, std::string const &filename) {
	return parse(::util::readEntireStream(sourceStream), filename);
}

Prol16ExeFile Prol16ExeFile::parse(::util::FileBuffer const &buffer, std::string const &filename) {
	checkFileSize(buffer.size(), filename);
	checkFileStartsWithMagicNumber(buffer, filename);

	auto const entryPointAddress = ::util::readValue<Address>(buffer, EntryPointAddressOffset);

	CodeSegment::size_type const codeSegmentSize = (buffer.size() - CodeSegmentOffset) / sizeof(CodeSegment::value_type);
	CodeSegment codeSegment(codeSegmentSize);
	std::memcpy(codeSegment.data(), buffer.data() + CodeSegmentOffset, buffer.size() - CodeSegmentOffset);

	return Prol16ExeFile(entryPointAddress, std::move(codeSegment));
}

void Prol16ExeFile::checkFileSize(::util::FileBuffer::size_type const bufferSize, std::string const &filename) {
	if (bufferSize < EntryPointAddressOffset) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::MagicNumberSize);
	}

	if (bufferSize < CodeSegmentOffset) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::EntryPoint);
	}

	if (bufferSize == CodeSegmentOffset) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::CodeSegment);
	}

	if (!::util::isMultiple(sizeof(Data), bufferSize - CodeSegmentOffset)) {
		std::ostringstream errorMessage;
		errorMessage << "actual buffer size of the code segment (" << bufferSize - CodeSegmentOffset << ") ";
		errorMessage << "isn't a multiple of the data size (" << sizeof(Data) << "); ";
		errorMessage << "this indicates incomplete instructions!";

		throw std::runtime_error(errorMessage.str());
	}
}

void Prol16ExeFile::checkFileStartsWithMagicNumber(::util::FileBuffer const &buffer, std::string const &filename) {
	if (!std::equal(MagicNumber.cbegin(), MagicNumber.cend(), buffer.cbegin())) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::MagicNumberValue);
	}
}

Prol16ExeFile::Prol16ExeFile(Address const entryPointAddress, CodeSegment codeSegment)
: entryPointAddress(entryPointAddress), codeSegment(std::move(codeSegment)) {}

}	// namespace util
}	// namespace PROL16
