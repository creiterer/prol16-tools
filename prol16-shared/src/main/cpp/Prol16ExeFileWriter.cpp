/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Prol16ExeFileWriter.h"

#include "FileUtils.h"
#include "InstructionWriter.h"
#include "Prol16ExeFile.h"
#include "RegisterUtils.h"
#include "StringUtils.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

Prol16ExeFileWriter::Prol16ExeFileWriter(std::string const &filename,
										 LabelTable const &labels, Address const stringsStartAddress)
: filename(filename), fileStream(filename, std::ofstream::binary), symbolTable(SymbolTable::create(labels, stringsStartAddress)) {
	if (!fileStream) {
		throw std::ios_base::failure("Failed to open PROL16 executable file '" + filename + "'");
	}
}

Prol16ExeFileWriter::~Prol16ExeFileWriter() {
	fileStream.close();
}

void Prol16ExeFileWriter::writeFileHeader(std::string const &entryPointName) {
	writeMagicNumber();
	writeEntryPointAddress(entryPointName);
}

void Prol16ExeFileWriter::writeMagicNumber() {
	std::ostream_iterator<char> ostreamItor(fileStream);
	std::copy(Prol16ExeFile::MagicNumber.cbegin(), Prol16ExeFile::MagicNumber.cend(), ostreamItor);
}

void Prol16ExeFileWriter::writeEntryPointAddress(std::string const &entryPointName) {
	try {
		::util::writeValueBinary(fileStream, symbolTable.getSymbolAddress(entryPointName));
	} catch (std::out_of_range const&) {
		throw std::runtime_error(::util::format("FAILED: Writing PROL16 exe file: Writing file header: Could not find address of entry point '%s'", entryPointName.c_str()));
	}
}

void Prol16ExeFileWriter::writeSymbolTable() {
	::util::writeValueBinary(fileStream, symbolTable.size());

	for (SymbolTable::Entry const &entry : symbolTable) {
		::util::writeValueBinary(fileStream, entry.first);
		::util::writeValueBinary(fileStream, entry.second.second);
	}
}

void Prol16ExeFileWriter::writeSymbolNames() {
	for (SymbolTable::Entry const &entry : symbolTable) {
		::util::writeStringToStream(fileStream, entry.second.first);
	}
}

}	// namespace util
}	// namespace PROL16
