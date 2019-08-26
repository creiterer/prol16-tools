/**
 * @author		creiterer
 * @date 		2019-08-25
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED

#include "MemoryUtils.h"
#include "NonCopyable.h"

#include <fstream>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class Prol16ExeFileWriter final : private ::util::NonCopyable {	// NOLINT(cppcoreguidelines-special-member-functions)
public:
	explicit Prol16ExeFileWriter(std::string const &filename);
	~Prol16ExeFileWriter() override;

	inline std::ofstream& stream() { return fileStream; }
	inline std::string getFilename() const { return filename; }

	void writeFileHeader(memory::Address const entryPointAddress);

private:
	std::string const filename;
	std::ofstream fileStream;

	void writeMagicNumber();
};


}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_PROL16EXEFILEWRITER_H_INCLUDED */
