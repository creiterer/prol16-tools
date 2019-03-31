/**
 * @author		creiterer
 * @date 		2019-03-26
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "CLIArguments.h"

#include <sstream>

#include "CLIError.h"

namespace util {

CLIArguments CLIArguments::parse(int const argc, char const * const argv[]) {
	if (!isArgumentCountValid(argc)) {
		throw CLIError("invalid number of arguments");
	}

	if (argc == 2) {
		validateFilename(argv[1]);
		return CLIArguments(argv[1], false);
	} else if (argc == 3) {
		validateOption(argv[1]);
		validateFilename(argv[2]);
		return CLIArguments(argv[2], true);
	}

	throw CLIError("failed to parse cli arguments");
}

bool CLIArguments::isArgumentCountValid(int const argc) {
	switch (argc) {
	case 2:
	case 3: return true;
	default: return false;
	}
}

bool CLIArguments::isOptionValid(std::string const &option) {
	if (option != "-c") { return false; }

	return true;
}

CLIArguments::CLIArguments(std::string const &filename, bool const printToConsole) : filename(filename), printToConsole(printToConsole) {

}

void CLIArguments::validateFilename(std::string const &filename) {
	if (filename.at(0) == '-') {
		std::ostringstream errorMessage;
		errorMessage << "invalid usage: expected filename but got option '" << filename << "'";

		throw CLIError(errorMessage.str());
	}
}

void CLIArguments::validateOption(std::string const &option) {
	if (!isOptionValid(option)) {
		std::ostringstream errorMessage;
		errorMessage << "invalid option: '" << option << "'";

		throw CLIError(errorMessage.str());
	}
}

}
