/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing a PROL16 executable file.
 */

#include "Prol16ExeFile.h"

#include "FileUtils.h"
#include "MathUtils.h"
#include "Prol16ExeParseError.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <utility>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

constexpr char const *Prol16ExeFile::Extension;
constexpr std::array<unsigned char, Prol16ExeFile::MagicNumberSize> Prol16ExeFile::MagicNumber;

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
	auto const initFuncAddress = ::util::readValue<Address>(buffer, InitFuncAddressOffset);

	auto const symbolTableSize = ::util::readValue<Data>(buffer, SymbolTableSizeOffset);
	assert(symbolTableSize != 0);

	std::vector<std::pair<Address, Address>> symbolAddresses(symbolTableSize);
	// NOLINTNEXTLINE(bugprone-undefined-memory-manipulation)
	std::memcpy(symbolAddresses.data(), buffer.data() + SymbolTableOffset, symbolTableSize * (2 * sizeof(Address)));

	SymbolTable::SymbolAddressTable symbolAddressTable;
	for (auto const &entry : symbolAddresses) {
		symbolAddressTable.emplace(entry.first, entry.second);
	}

	unsigned const codeSegmentOffset = SymbolTableOffset + symbolTableSize * (2 * sizeof(Address));
	CodeSegment codeSegment = CodeSegment::createFromFileBuffer(buffer, codeSegmentOffset);

	SymbolTable::StringTable stringTable;
	for (auto const &entry : symbolAddresses) {
		stringTable.emplace(entry.second, codeSegment.readString(entry.second));
	}

	return Prol16ExeFile(entryPointAddress, initFuncAddress, std::move(codeSegment), SymbolTable::create(symbolAddressTable, stringTable));
}

void Prol16ExeFile::checkFileSize(::util::FileBuffer::size_type const bufferSize, std::string const &filename) {
	if (bufferSize < EntryPointAddressOffset) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::MagicNumberSize);
	}

	if (bufferSize < SymbolTableSizeOffset) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::EntryPoint);
	}

	if (bufferSize < SymbolTableOffset) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::SymbolTableSize);
	}

	if (bufferSize == SymbolTableOffset) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::SymbolTable);
	}
}

void Prol16ExeFile::checkFileStartsWithMagicNumber(::util::FileBuffer const &buffer, std::string const &filename) {
	if (!std::equal(MagicNumber.cbegin(), MagicNumber.cend(), buffer.cbegin())) {
		throw Prol16ExeParseError(filename, Prol16ExeParseError::ErrorType::MagicNumberValue);
	}
}

Prol16ExeFile::Prol16ExeFile(Address const entryPointAddress, Address const initFuncAddress, CodeSegment codeSegment, SymbolTable symbolTable)
: entryPointAddress(entryPointAddress), initFuncAddress(initFuncAddress), codeSegment(std::move(codeSegment)), symbolTable(std::move(symbolTable)) {

}

}	// namespace util
}	// namespace PROL16
