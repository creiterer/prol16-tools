/**
 * @author		creiterer
 * @date 		2019-03-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Main function that instantiates the lexer and parser, parses the input file,
 * 				and walks through the parse tree, writing the instructions to a file.
 */

#include "antlr4-runtime.h"
#include "CountingErrorListener.h"
#include "LabelListener.h"
#include "Prol16AsmLexer.h"
#include "Prol16AsmListener.h"
#include "Prol16AsmParser.h"

#include "ArgumentParser.h"
#include "CLIArguments.h"
#include "CLIError.h"
#include "Filename.h"
#include "InstructionWriter.h"
#include "Prol16ExeFile.h"
#include "Prol16ExeFileWriter.h"
#include "ScopedFileStream.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace antlr4;
using std::cout;
using std::cerr;
using std::endl;
using util::ScopedFileStream;
using PROL16::util::Prol16ExeFile;
using PROL16::util::Prol16ExeFileWriter;
using PROL16::util::InstructionWriter;

static char const * const FILENAME_ARG_NAME = "PROL16_ASSEMBLY_FILE"; 	// NOLINT(readability-identifier-naming)

static char const * const EntryPointName = "main";

int main(int const argc, char const * const argv[]) {
	try {
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

		Prol16ExeFileWriter p16ExeFile(filename.getWithCustomExtension(Prol16ExeFile::Extension));

		PROL16::Prol16AsmParser parser(&tokens);
		parser.addErrorListener(&countingErrorListener);

		tree::ParseTree *parseTree = parser.prol16AsmFile();

		cout << "compiling '" << filename.asString() << "' to '" << p16ExeFile.getFilename() << "': ";
		if (countingErrorListener.hasFoundErrors()) {
			cout << "FAILED: " << countingErrorListener.getErrorCount() << " error(s) detected while parsing" << endl;
			return 2;
		}

		PROL16::LabelListener labelListener;
		tree::ParseTreeWalker::DEFAULT.walk(&labelListener, parseTree);

		InstructionWriter instructionWriter;
		PROL16::Prol16AsmListener asmListener(instructionWriter, labelListener.getLabels());
		tree::ParseTreeWalker::DEFAULT.walk(&asmListener, parseTree);

		try {
			p16ExeFile.writeFileHeader(labelListener.getLabelAddress(EntryPointName));
		} catch (std::out_of_range const&) {
			cout << "FAILED: Could not find address of entry point '" << EntryPointName << "'" << endl;
			return 2;
		}

		instructionWriter.writeBufferToStream(p16ExeFile.stream());

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
