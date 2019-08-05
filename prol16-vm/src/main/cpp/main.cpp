#include <iostream>
#include <string>

#include "VirtualMachine.h"

#include "RegisterUtils.h"
#include "ArgumentParser.h"
#include "CLIArguments.h"
#include "CLIError.h"
#include "CLIFlags.h"

using std::cerr;
using std::endl;

static std::string const FILENAME_ARG_NAME = "PROL16_EXE_FILE";

int main(int const argc, char const * const argv[]) {
	try {
		util::cli::ArgumentParser argumentParser;
		argumentParser.addPositionalArgument(FILENAME_ARG_NAME);
		argumentParser.addFlag(util::cli::flags::VERBOSE, false);

		util::cli::CLIArguments const cliArguments = argumentParser.parseArguments(argc, argv);

		PROL16::VirtualMachine prol16vm(cliArguments[FILENAME_ARG_NAME], cliArguments.isSet(util::cli::flags::VERBOSE));
		prol16vm.run();

		return 0;
	} catch (util::cli::CLIError const &e) {
		cerr << "CLI Error: " << e.what() << endl;
		return 2;
	} catch (std::ios_base::failure const &f) {
        cerr << "Error: Caught an ios_base::failure." << endl;
        cerr << "Error Message: " << f.what() << endl;
        cerr << "Error Code: " << f.code() << endl;
        return 1;
	} catch (std::exception const &e) {
        cerr << "Error: Caught an std::exception." << endl;
        cerr << "Error Message: " << e.what() << endl;
        return 1;
	} catch (...) {
        cerr << "Error: Caught an unexpected exception." << endl;
        return 1;
	}
}
