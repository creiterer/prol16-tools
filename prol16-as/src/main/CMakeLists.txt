#### GENERAL SETUP ####

# -Wno-unused-parameter is needed for ANTLR semantic predicates
# -Wno-extra-semi is needed for ANTLR
set(WARNING_FLAGS "-Wno-unused-parameter -Wno-extra-semi")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")

#### ANTLR SETUP ####

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# somehow CMAKE_MODULE_PATH doesn't work because, although it is set,
# find_package() can't find the appropriate files!
set(antlr4-runtime_DIR "${PROJECT_SOURCE_DIR}/cmake")
set(antlr4-generator_DIR "${PROJECT_SOURCE_DIR}/cmake")

# bring in the required ANTLRv4 packages
find_package(antlr4-runtime CONFIG REQUIRED)
find_package(antlr4-generator CONFIG REQUIRED)

# set path to grammar files
get_filename_component(GRAMMAR_DIR "grammar/" ABSOLUTE)

# set path to parser generator
set(ANTLR4_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-4.7.2-complete.jar)

# generate lexer
antlr4_generate( 
    PROL16_AS_LEXER
    ${GRAMMAR_DIR}/Prol16AsmLexer.g4
    LEXER
    FALSE
    FALSE
    "PROL16"
)

# generate parser
antlr4_generate( 
    PROL16_AS_PARSER
    ${GRAMMAR_DIR}/Prol16AsmParser.g4
    PARSER
    TRUE
    FALSE
    "PROL16"
    "${ANTLR4_TOKEN_FILES_PROL16_AS_LEXER}"
    "${ANTLR4_TOKEN_DIRECTORY_PROL16_AS_LEXER}"
)

#### TARGET SETUP ####

get_filename_component(MAIN_CPP_DIR "cpp/" ABSOLUTE)
set(MAIN_CPP_SOURCES
    ${MAIN_CPP_DIR}/main.cpp
    ${MAIN_CPP_DIR}/Prol16AsmListener.cpp
    ${MAIN_CPP_DIR}/InstructionWriter.cpp
    ${MAIN_CPP_DIR}/CommandCounter.cpp
    ${MAIN_CPP_DIR}/LabelListener.cpp
    ${MAIN_CPP_DIR}/ContextUtils.cpp
)

# add directories for generated include files
include_directories(${PROJECT_BINARY_DIR} ${ANTLR4_INCLUDE_DIR} ${ANTLR4_INCLUDE_DIR_PROL16_AS_LEXER} ${ANTLR4_INCLUDE_DIR_PROL16_AS_PARSER})

add_executable(prol16-as ${MAIN_CPP_SOURCES} ${ANTLR4_SRC_FILES_PROL16_AS_LEXER} ${ANTLR4_SRC_FILES_PROL16_AS_PARSER})
target_link_libraries(prol16-as antlr4_static prol16shared)
