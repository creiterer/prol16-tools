/**
 * @author		creiterer
 * @date 		2019-08-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Helper class for writing PROL16 executable files.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED

#include "InstructionWriter.h"
#include "LabelUtils.h"
#include "Logger.h"
#include "MemoryUtils.h"
#include "NonCopyable.h"
#include "SymbolTable.h"

#include <fstream>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class Prol16ExeFileWriter final : private ::util::NonCopyable {	// NOLINT(cppcoreguidelines-special-member-functions)
public:
	using Address = memory::Address;
	using Data = memory::Data;
	using Segment = InstructionWriter::Segment;

	static Data const MagicStdLibValue = 0xBAAD;

	Prol16ExeFileWriter(std::string const &filename,
						LabelTable const &labels, Address const stringsStartAddress,
						::util::logging::Logger &logger);
	~Prol16ExeFileWriter() override;

	inline std::ofstream& stream() { return fileStream; }
	inline std::string getFilename() const { return filename; }

	void writeFileHeader(std::string const &entryPointName, std::string const &initFuncName = "");
	void writeSymbolTable();
	void writeCodeSegment(Segment const &segment);
	void writeDataSegment(Segment const &segment);

private:
	std::string const filename;
	std::ofstream fileStream;
	SymbolTable const symbolTable;
	::util::logging::Logger &logger;

	void writeMagicNumber();
	void writeSymbolAddress(std::string const &symbolName, std::string const &symbolDescription);
	void writeStringTable();
	void logSymbolTableEntry(SymbolTable::Entry const &entry);
	void logStringTableEntry(SymbolTable::StringTableEntry const &entry);
};


}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED */
