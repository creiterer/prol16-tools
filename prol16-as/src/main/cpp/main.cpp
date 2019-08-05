/**
 * @author		creiterer
 * @date 		2019-03-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Main function that instantiates the lexer and parser, parses the input file,
 * 				and walks through the parse tree, writing the instructions to a file.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "antlr4-runtime.h"
#include "Prol16AsmLexer.h"
#include "Prol16AsmParser.h"
#include "Prol16AsmListener.h"
#include "LabelListener.h"
#include "CountingErrorListener.h"

#include "ScopedFileStream.h"
#include "Filename.h"
#include "InstructionWriter.h"
#include "ArgumentParser.h"
#include "CLIArguments.h"
#include "CLIError.h"

using namespace antlr4;
using std::cout;
using std::cerr;
using std::endl;
using util::ScopedFileStream;

//static void printUsage(std::string const &errorMessage, std::string const &appName) {
//	cerr << errorMessage << endl;
//	cerr << "Usage: " << appName << " PROL16_ASSEMBLY_FILE" << endl;
//}

static std::string const FILENAME_ARG_NAME = "PROL16_ASSEMBLY_FILE";

int main(int const argc, char const * const argv[]) {
	try {
//		if (argc != 2) {
//			std::ostringstream errorMessage;
//			errorMessage << "Error: expected exactly one PROL16 assembly input file but got " << (argc - 1);
//			printUsage(errorMessage.str(), argv[0]);
//			return 1;
//		}
		util::cli::ArgumentParser argumentParser;
		argumentParser.addPositionalArgument(FILENAME_ARG_NAME);

		util::cli::CLIArguments const cliArguments = argumentParser.parseArguments(argc, argv);

		cout << "========== Compilation Started ==========" << endl;

		util::Filename filename(cliArguments[FILENAME_ARG_NAME]);

		ScopedFileStream<std::ifstream> inputFileStream(filename.asString(), std::ifstream::in);
		ANTLRInputStream inputStream(inputFileStream.stream());

		PROL16::CountingErrorListener countingErrorListener;

		PROL16::Prol16AsmLexer lexer(&inputStream);
		lexer.addErrorListener(&countingErrorListener);

		CommonTokenStream tokens(&lexer);

		ScopedFileStream<std::ofstream> exeFileStream(filename.getWithCustomExtension("p16"), std::ofstream::binary);

		PROL16::Prol16AsmParser parser(&tokens);
		parser.addErrorListener(&countingErrorListener);

		tree::ParseTree *parseTree = parser.prol16AsmFile();

		cout << "compiling '" << filename.asString() << "' to '" << exeFileStream.getFilename() << "': ";
		if (countingErrorListener.hasFoundErrors()) {
			cout << "FAILED: " << countingErrorListener.getErrorCount() << " error(s) detected while parsing" << endl;
			return 2;
		}

		PROL16::LabelListener labelListener;
		tree::ParseTreeWalker::DEFAULT.walk(&labelListener, parseTree);

		PROL16::InstructionWriter instructionWriter;
		PROL16::Prol16AsmListener asmListener(instructionWriter, labelListener.getLabels());
		tree::ParseTreeWalker::DEFAULT.walk(&asmListener, parseTree);

		instructionWriter.writeBufferToStream(exeFileStream);

		cout << "SUCCEEDED" << endl;
		cout << "========== Compilation Finished ==========" << endl;

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
