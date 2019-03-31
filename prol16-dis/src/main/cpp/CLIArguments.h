/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_CLIARGUMENTS_H_INCLUDED
#define PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_CLIARGUMENTS_H_INCLUDED

#include <string>

namespace util {

class CLIArguments final {
public:
	static CLIArguments parse(int const argc, char const * const argv[]);

	static bool isArgumentCountValid(int const argc);

	static bool isOptionValid(std::string const &option);

	CLIArguments(std::string const &filename, bool const printToConsole);

	inline std::string getFilename() const { return filename; }
	inline bool shouldPrintToConsole() const { return printToConsole; }

private:
	std::string const filename;
	bool const printToConsole;

	static void validateFilename(std::string const &filename);
	static void validateOption(std::string const &option);
};

}

#endif /* PROL16_ASM_PROL16_DIS_SRC_MAIN_CPP_CLIARGUMENTS_H_INCLUDED */
