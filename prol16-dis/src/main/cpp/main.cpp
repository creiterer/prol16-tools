/**
 * @author		creiterer
 * @date 		2019-03-18
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Main function that instantiates the disassembler and
 * 				writes the disassembled instructions to a designated output stream.
 */


#include "Disassembler.h"

#include "ArgumentParser.h"
#include "CLIArguments.h"
#include "CLIError.h"
#include "Filename.h"
#include "ScopedFileStream.h"

#include <fstream>
#include <iostream>
#include <sstream>

using std::cout;
using std::cerr;
using std::endl;
using util::ScopedFileStream;

namespace {

void disassemble(std::string const &filename, std::ostream &outputStream) {
	ScopedFileStream<std::ifstream> inputFileStream(filename, std::ifstream::binary);

	PROL16::Disassembler disassembler(inputFileStream, outputStream);
	disassembler.disassemble();
}

void disassembleToConsole(std::string const &filename) {
	disassemble(filename, std::cout);
}

void disassembleToFile(util::Filename const &filename) {
	cout << "========== Decompilation Started ==========" << endl;

	ScopedFileStream<std::ofstream> assemblyFileStream(filename.appendToName("_dis").getWithCustomExtension("s"), std::ofstream::out);
	cout << "decompiling '" << filename.asString() << "' to '" << assemblyFileStream.getFilename() << "': ";

	disassemble(filename.asString(), assemblyFileStream);

	cout << "SUCCEEDED" << endl;
	cout << "========== Decompilation Finished ==========" << endl;
}

}	// anonymous namespace

static std::string const FILENAME_ARG_NAME = "PROL16_EXE_FILE";		// NOLINT(readability-identifier-naming)

int main(int const argc, char const * const argv[]) {
	using namespace util;

	try {
		cli::ArgumentParser argumentParser("PROL16 Disassembler");
		argumentParser.addPositionalArgument(FILENAME_ARG_NAME);
		argumentParser.addFlag("-c", "--console", false);

		cli::CLIArguments const cliArguments = argumentParser.parseArguments(argc, argv);

		if (cliArguments.isHelp()) {
			argumentParser.showUsageMessage(std::cerr);
			return 0;
		}

		if (cliArguments.isSet("-c")) {
			disassembleToConsole(cliArguments[FILENAME_ARG_NAME]);
		} else {
			Filename filename(cliArguments[FILENAME_ARG_NAME]);
			disassembleToFile(filename);
		}

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
