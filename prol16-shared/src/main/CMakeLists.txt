#### TARGET SETUP ####

get_filename_component(MAIN_CPP_DIR "cpp/" ABSOLUTE)
set(MAIN_CPP_SOURCES
    ${MAIN_CPP_DIR}/Filename.cpp
    ${MAIN_CPP_DIR}/Instruction.cpp
    ${MAIN_CPP_DIR}/MnemonicUtils.cpp
    ${MAIN_CPP_DIR}/NumberUtils.cpp
    ${MAIN_CPP_DIR}/RegisterUtils.cpp
    ${MAIN_CPP_DIR}/StringUtils.cpp
    ${MAIN_CPP_DIR}/FileUtils.cpp
    ${MAIN_CPP_DIR}/RegisterError.cpp
    ${MAIN_CPP_DIR}/OpcodeError.cpp
    ${MAIN_CPP_DIR}/InstructionDecodeError.cpp
    ${MAIN_CPP_DIR}/IncompleteInstructionError.cpp
    ${MAIN_CPP_DIR}/CLIArguments.cpp
    ${MAIN_CPP_DIR}/CLIArgumentsBuilder.cpp
    ${MAIN_CPP_DIR}/ArgumentParser.cpp
    ${MAIN_CPP_DIR}/Logger.cpp
    ${MAIN_CPP_DIR}/Prol16ExeFileWriter.cpp
    ${MAIN_CPP_DIR}/Prol16ExeFile.cpp
    ${MAIN_CPP_DIR}/Prol16ExeParseError.cpp
    ${MAIN_CPP_DIR}/InstructionWriter.cpp
    ${MAIN_CPP_DIR}/CommandInterpreter.cpp
    ${MAIN_CPP_DIR}/RuntimeLibrary.cpp
    ${MAIN_CPP_DIR}/MemoryUtils.cpp
    ${MAIN_CPP_DIR}/SymbolTable.cpp
    ${MAIN_CPP_DIR}/CodeSegment.cpp
    ${MAIN_CPP_DIR}/ArithmeticResult.cpp
    ${MAIN_CPP_DIR}/CLIArgumentNames.cpp
    ${MAIN_CPP_DIR}/Flavor.cpp
    ${MAIN_CPP_DIR}/IntegerUtils.cpp
)

add_library(prol16shared STATIC ${MAIN_CPP_SOURCES})

set(PROL16SHARED_INCLUDE_DIR
    ${MAIN_CPP_DIR}
)

target_include_directories(prol16shared SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${PROL16SHARED_INCLUDE_DIR}>"
)
