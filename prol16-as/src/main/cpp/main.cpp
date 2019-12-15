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
#include "CLIArgumentNames.h"
#include "CLIArguments.h"
#include "CLIError.h"
#include "Filename.h"
#include "InstructionWriter.h"
#include "Logger.h"
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

constexpr char const *FILENAME_ARG_NAME = "PROL16_ASSEMBLY_FILE"; 	// NOLINT(readability-identifier-naming)

constexpr char const *CEntryPointName = "main";
constexpr char const *GoEntryPointName = "main.main";

int main(int const argc, char const * const argv[]) {
	try {
		util::cli::ArgumentParser argumentParser("PROL16 Assembler");
		argumentParser.addPositionalArgument(FILENAME_ARG_NAME);
		argumentParser.addOptionalArgument(util::cli::options::LOGFILE, "prol16-as.log");
		argumentParser.addFlag(util::cli::flags::VERBOSE, false);

		util::cli::CLIArguments const cliArguments = argumentParser.parseArguments(argc, argv);

		if (cliArguments.isHelp()) {
			argumentParser.showUsageMessage(std::cerr);
			return 0;
		}

		util::ScopedFileStream<std::ofstream> logFileStream(cliArguments[util::cli::options::LOGFILE], std::ofstream::out);
		util::logging::Logger::LogStreams alwaysLogStreams{std::cout};

		util::logging::Logger logger({std::cout, logFileStream.stream()}, cliArguments.isSet(util::cli::flags::VERBOSE));

		logger.ifDisabledLogTo(alwaysLogStreams) << "========== Compilation Started ==========\n";

		util::Filename filename(cliArguments[FILENAME_ARG_NAME]);

		ScopedFileStream<std::ifstream> inputFileStream(filename.asString(), std::ifstream::in);
		ANTLRInputStream inputStream(inputFileStream.stream());

		PROL16::CountingErrorListener countingErrorListener;

		PROL16::Prol16AsmLexer lexer(&inputStream);
		lexer.addErrorListener(&countingErrorListener);

		CommonTokenStream tokens(&lexer);

		PROL16::Prol16AsmParser parser(&tokens);
		parser.addErrorListener(&countingErrorListener);

		tree::ParseTree *parseTree = parser.prol16AsmFile();

		std::string const p16ExeFilename = filename.getWithCustomExtension(Prol16ExeFile::Extension);

		logger.ifDisabledLogTo(alwaysLogStreams) << "compiling '" << filename.asString() << "' to '" << p16ExeFilename << "': ";
		if (countingErrorListener.hasFoundErrors()) {
			logger.ifDisabledLogTo(alwaysLogStreams) << "FAILED: " << countingErrorListener.getErrorCount() << " error(s) detected while parsing\n";
			return 2;
		}

		if (logger.isEnabled()) {
			alwaysLogStreams << '\n';
		}

		PROL16::LabelListener labelListener;
		tree::ParseTreeWalker::DEFAULT.walk(&labelListener, parseTree);

		InstructionWriter instructionWriter;
		PROL16::Prol16AsmListener asmListener(instructionWriter, labelListener.getLabels());
		tree::ParseTreeWalker::DEFAULT.walk(&asmListener, parseTree);

		Prol16ExeFileWriter p16ExeFile(p16ExeFilename,
									   labelListener.getLabels(), labelListener.getNextInstructionAddress(),
									   logger);

		if (labelListener.containsLabel(CEntryPointName)) {
			p16ExeFile.writeFileHeader(CEntryPointName);
		} else {
			p16ExeFile.writeFileHeader(GoEntryPointName);
		}

		p16ExeFile.writeSymbolTable();
		p16ExeFile.writeCodeSegment(instructionWriter.getInstructionBuffer());

		logger.ifDisabledLogTo(alwaysLogStreams) << "SUCCEEDED\n";
		logger.ifDisabledLogTo(alwaysLogStreams) << "========== Compilation Finished ==========\n";

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
