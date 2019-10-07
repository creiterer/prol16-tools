/**
 * @author		creiterer
 * @date 		2019-08-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED

#include "LabelUtils.h"
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

	static memory::Data const MagicStdLibValue = 0xBAAD;

	Prol16ExeFileWriter(std::string const &filename,
						LabelTable const &labels, Address const stringsStartAddress);
	~Prol16ExeFileWriter() override;

	inline std::ofstream& stream() { return fileStream; }
	inline std::string getFilename() const { return filename; }

	void writeFileHeader(std::string const &entryPointName);
	void writeSymbolTable();
	void writeSymbolNames();

private:
	std::string const filename;
	std::ofstream fileStream;
	SymbolTable const symbolTable;

	void writeMagicNumber();
	void writeEntryPointAddress(std::string const &entryPointName);

};


}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED */
