#include <iostream>
#include <string>

#include "VirtualMachine.h"

#include "RegisterUtils.h"

using std::cerr;
using std::endl;

static void printUsage(std::string const &errorMessage, std::string const &appName) {
	cerr << errorMessage << endl;
	cerr << "Usage: " << appName << " PROL16_EXE_FILE" << endl;
}

int main(int const argc, char const * const argv[]) {
	// TODO: exception handling
	if (argc != 2) {
		printUsage("Error: invalid number of arguments", argv[0]);
		return 1;
	}

	PROL16::VirtualMachine prol16vm(argv[1]);
	prol16vm.run();

	return 0;
}
