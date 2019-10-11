/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "Prol16ExeFileWriter.h"

#include "FileUtils.h"
#include "InstructionWriter.h"
#include "NumberUtils.h"
#include "Prol16ExeFile.h"
#include "RegisterUtils.h"
#include "StringUtils.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

using ::util::logging::Logger;

Prol16ExeFileWriter::Prol16ExeFileWriter(std::string const &filename,
										 LabelTable const &labels, Address const stringsStartAddress,
										 ::util::logging::Logger &logger)
: filename(filename), fileStream(filename, std::ofstream::binary),
  symbolTable(SymbolTable::create(labels, stringsStartAddress)),
  logger(logger) {
	if (!fileStream) {
		throw std::ios_base::failure("Failed to open PROL16 executable file '" + filename + "'");
	}
}

Prol16ExeFileWriter::~Prol16ExeFileWriter() {
	fileStream.close();
}

void Prol16ExeFileWriter::writeFileHeader(std::string const &entryPointName) {
	logger << "writing file header ...\n";
	writeMagicNumber();
	writeEntryPointAddress(entryPointName);
}

void Prol16ExeFileWriter::writeMagicNumber() {
	std::ostream_iterator<char> ostreamItor(fileStream);
	std::copy(Prol16ExeFile::MagicNumber.cbegin(), Prol16ExeFile::MagicNumber.cend(), ostreamItor);
}

void Prol16ExeFileWriter::writeEntryPointAddress(std::string const &entryPointName) {
	try {
		Address const entryPointAddress = symbolTable.getSymbolAddress(entryPointName);

		logger.forEachLogStream([entryPointName, entryPointAddress](Logger::LogStream stream){
			stream << "writing entry point address: entry point name = '" << entryPointName << "' | entry point address = ";
			util::printHexNumberFormattedWithBase(stream, entryPointAddress);
			stream << '\n';
		});

		::util::writeValueBinary(fileStream, entryPointAddress);
	} catch (std::out_of_range const&) {
		throw std::runtime_error(::util::format("FAILED: Writing PROL16 exe file: Writing file header: Could not find address of entry point '%s'", entryPointName.c_str()));
	}
}

void Prol16ExeFileWriter::writeSymbolTable() {
	logger << "writing symbol table ...\n";

	::util::writeValueBinary<Data>(fileStream, symbolTable.size());
	logger << "symbol table size = " << std::dec << symbolTable.size() << '\n';

	for (SymbolTable::Entry const &entry : symbolTable) {
		logSymbolTableEntry(entry);
		::util::writeValueBinary(fileStream, entry.first);
		::util::writeValueBinary(fileStream, entry.second.second);
	}
}

void Prol16ExeFileWriter::writeCodeSegment(InstructionWriter::InstructionBuffer const &buffer) {
	::util::writeBufferToStream(fileStream, buffer);
	writeStringTable();
}

void Prol16ExeFileWriter::writeStringTable() {
	logger << "writing string table ...\n";

	for (SymbolTable::StringTableEntry const &entry : symbolTable.getStringTable()) {
		logStringTableEntry(entry);
		::util::writeStringPaddedToStream(fileStream, entry.second, sizeof(Data));
	}
}

void Prol16ExeFileWriter::logSymbolTableEntry(SymbolTable::Entry const &entry) {
	logger.forEachLogStream([entry](Logger::LogStream stream){
		stream << "writing symbol table entry: symbol address = ";
		util::printHexNumberFormattedWithBase(stream, entry.first);
		stream << " | symbol name address = ";
		util::printHexNumberFormattedWithBase(stream, entry.second.second);
		stream << '\n';
	});
}

void Prol16ExeFileWriter::logStringTableEntry(SymbolTable::StringTableEntry const &entry) {
	logger.forEachLogStream([entry](Logger::LogStream stream){
		stream << "writing string table entry: symbol name address = ";
		util::printHexNumberFormattedWithBase(stream, entry.first);
		stream << " | symbol name = '" << entry.second << "'\n";
	});
}

}	// namespace util
}	// namespace PROL16
