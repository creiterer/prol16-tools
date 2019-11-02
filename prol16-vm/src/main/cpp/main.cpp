/**
 * @author		creiterer
 * @date 		2019-03-31
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Main function running the PROL16 virtual machine.
 */

#include "VirtualMachine.h"

#include "ArgumentParser.h"
#include "CLIArgumentNames.h"
#include "CLIArguments.h"
#include "CLIError.h"
#include "Logger.h"
#include "RegisterUtils.h"
#include "ScopedFileStream.h"

#include <iostream>
#include <string>

using std::cerr;
using std::endl;

static std::string const FILENAME_ARG_NAME = "PROL16_EXE_FILE";				// NOLINT(readability-identifier-naming)
static util::cli::ArgumentName const DECIMAL_FLAG{"-d", "--decimal"};	// NOLINT(readability-identifier-naming)

int main(int const argc, char const * const argv[]) {
	try {
		util::cli::ArgumentParser argumentParser("PROL16 Virtual Machine");
		argumentParser.addPositionalArgument(FILENAME_ARG_NAME);
		argumentParser.addOptionalArgument(util::cli::options::LOGFILE, "prol16-vm.log");
		argumentParser.addFlag(util::cli::flags::INTERACTIVE, false);
		argumentParser.addFlag(util::cli::flags::VERBOSE, false);
		argumentParser.addFlag(DECIMAL_FLAG, false);

		util::cli::CLIArguments const cliArguments = argumentParser.parseArguments(argc, argv);

		if (cliArguments.isHelp()) {
			argumentParser.showUsageMessage(std::cerr);
			return 0;
		}

		bool const verboseLoggingEnabled = cliArguments.isSet(util::cli::flags::VERBOSE);

		util::logging::Logger logger(std::cout, verboseLoggingEnabled);

		util::ScopedFileStream<std::ofstream> logFileStream;

		if (verboseLoggingEnabled) {
			logFileStream.open(cliArguments[util::cli::options::LOGFILE], std::ofstream::out);
			logger.addLogStream(logFileStream.stream());
		}

		logger.logTimestamp("log created at: ", "\n");
		PROL16::VirtualMachine prol16vm(cliArguments[FILENAME_ARG_NAME], logger,
										cliArguments.isSet(util::cli::flags::INTERACTIVE), cliArguments.isSet(DECIMAL_FLAG));
		prol16vm.run();

		return 0;
	} catch (util::cli::CLIError const &e) {
		cerr << "\nCLI Error: " << e.what() << endl;
		return 2;
	} catch (std::ios_base::failure const &f) {
        cerr << "\nError: Caught an ios_base::failure." << endl;
        cerr << "Error Message: " << f.what() << endl;
        cerr << "Error Code: " << f.code() << endl;
        return 1;
	} catch (std::exception const &e) {
        cerr << "\nError: Caught an std::exception." << endl;
        cerr << "Error Message: " << e.what() << endl;
        return 1;
	} catch (...) {
        cerr << "\nError: Caught an unexpected exception." << endl;
        return 1;
	}
}
