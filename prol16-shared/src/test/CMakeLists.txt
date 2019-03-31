#### TARGET SETUP ####

get_filename_component(TEST_CPP_DIR "cpp/" ABSOLUTE)
set(TEST_CPP_SOURCES
    ${TEST_CPP_DIR}/FilenameTest.cpp
    ${TEST_CPP_DIR}/InstructionTest.cpp
    ${TEST_CPP_DIR}/MnemonicUtilsTest.cpp
    ${TEST_CPP_DIR}/NumberUtilsTest.cpp
    ${TEST_CPP_DIR}/RegisterUtilsTest.cpp
)

# add directory of main include files (needed for the test executable)
include_directories("../main/cpp")

add_executable(prol16-shared-test ${TEST_CPP_SOURCES})
target_link_libraries(prol16-shared-test gtest_main prol16shared)
add_test(NAME prol16-shared-test COMMAND prol16-shared-test)