/**
 * @author		creiterer
 * @date 		2019-08-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Helper class for writing PROL16 executable files.
 */

#include "Prol16ExeFileWriter.h"

#include "FileUtils.h"
#include "InstructionWriter.h"
#include "NumberUtils.h"
#include "PrintUtils.h"
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

void Prol16ExeFileWriter::writeFileHeader(std::string const &entryPointName, std::string const &initFuncName) {
	logger << "writing file header ...\n";
	writeMagicNumber();
	writeSymbolAddress(entryPointName, "entry point");
	writeSymbolAddress(initFuncName, "init func");
}

void Prol16ExeFileWriter::writeMagicNumber() {
	std::ostream_iterator<char> ostreamItor(fileStream);
	std::copy(Prol16ExeFile::MagicNumber.cbegin(), Prol16ExeFile::MagicNumber.cend(), ostreamItor);
}

void Prol16ExeFileWriter::writeSymbolAddress(std::string const &symbolName, std::string const &symbolDescription) {
	if (symbolName.empty()) {
		::util::writeValueBinary(fileStream, util::memory::InvalidCodeAddress);
		return;
	}

	try {
		Address const symbolAddress = symbolTable.getSymbolAddress(symbolName);

		logger.forEachLogStream([&symbolName, &symbolAddress, &symbolDescription](Logger::LogStream stream){
			stream << "writing " << symbolDescription << " address: ";
			stream << symbolDescription << " name = '" << symbolName << "' | ";
			stream << symbolDescription << " address = ";
			::util::printHexNumberFormattedWithBase(stream, symbolAddress);
			stream << '\n';
		});

		::util::writeValueBinary(fileStream, symbolAddress);
	} catch (std::out_of_range const&) {
		throw std::runtime_error(::util::format("FAILED: Writing PROL16 exe file: Writing file header: Could not find address of %s '%s'",
												symbolDescription.c_str(), symbolName.c_str()));
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
		::util::printHexNumberFormattedWithBase(stream, entry.first);
		stream << " | symbol name address = ";
		::util::printHexNumberFormattedWithBase(stream, entry.second.second);
		stream << '\n';
	});
}

void Prol16ExeFileWriter::logStringTableEntry(SymbolTable::StringTableEntry const &entry) {
	logger.forEachLogStream([entry](Logger::LogStream stream){
		stream << "writing string table entry: symbol name address = ";
		::util::printHexNumberFormattedWithBase(stream, entry.first);
		stream << " | symbol name = '" << entry.second << "'\n";
	});
}

}	// namespace util
}	// namespace PROL16
