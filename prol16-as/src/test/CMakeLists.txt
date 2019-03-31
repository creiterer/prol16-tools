#### TARGET SETUP ####

get_filename_component(TEST_CPP_DIR "cpp/" ABSOLUTE)
set(TEST_CPP_SOURCES
    ${TEST_CPP_DIR}/InstructionWriterTest.cpp
    ${TEST_CPP_DIR}/CommandCounterTest.cpp
)

get_filename_component(MAIN_CPP_DIR "src/main/cpp/" ABSOLUTE BASE_DIR ${PROJECT_SOURCE_DIR})
set(MAIN_CPP_SOURCES
    ${MAIN_CPP_DIR}/InstructionWriter.cpp
    ${MAIN_CPP_DIR}/CommandCounter.cpp
)

# add directory of main include files (needed for the test executable)
include_directories(${MAIN_CPP_DIR})

add_executable(prol16-as-test ${TEST_CPP_SOURCES} ${MAIN_CPP_SOURCES})
target_link_libraries(prol16-as-test gtest_main prol16shared)
add_test(NAME prol16-as-test COMMAND prol16-as-test)