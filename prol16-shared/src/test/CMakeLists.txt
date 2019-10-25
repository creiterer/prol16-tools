#### TARGET SETUP ####

get_filename_component(TEST_CPP_DIR "cpp/" ABSOLUTE)
set(TEST_CPP_SOURCES
    ${TEST_CPP_DIR}/FilenameTest.cpp
    ${TEST_CPP_DIR}/InstructionTest.cpp
    ${TEST_CPP_DIR}/MnemonicUtilsTest.cpp
    ${TEST_CPP_DIR}/NumberUtilsTest.cpp
    ${TEST_CPP_DIR}/RegisterUtilsTest.cpp
    ${TEST_CPP_DIR}/StringUtilsTest.cpp
    ${TEST_CPP_DIR}/MathUtilsTest.cpp
    ${TEST_CPP_DIR}/FileUtilsTest.cpp
    ${TEST_CPP_DIR}/ArgumentParserTest.cpp
    ${TEST_CPP_DIR}/InstructionWriterTest.cpp
    ${TEST_CPP_DIR}/RuntimeLibraryTest.cpp
    ${TEST_CPP_DIR}/MemoryUtilsTest.cpp
    ${TEST_CPP_DIR}/ArithmeticResultTest.cpp
    ${TEST_CPP_DIR}/CLIArgumentNamesTest.cpp
)

# add directory of main include files (needed for the test executable)
include_directories("../main/cpp")

add_executable(prol16-shared-test ${TEST_CPP_SOURCES})
target_link_libraries(prol16-shared-test gtest_main prol16shared)
add_test(NAME prol16-shared-test COMMAND prol16-shared-test)

# copy the resource files
add_custom_command(TARGET prol16-shared-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_LIST_DIR}/resources/
            ${CMAKE_CURRENT_BINARY_DIR}/resources/)