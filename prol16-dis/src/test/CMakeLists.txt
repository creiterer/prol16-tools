#### TARGET SETUP ####

get_filename_component(TEST_CPP_DIR "cpp/" ABSOLUTE)
set(TEST_CPP_SOURCES
    ${TEST_CPP_DIR}/DisassemblerTest.cpp
)

get_filename_component(MAIN_CPP_DIR "src/main/cpp/" ABSOLUTE BASE_DIR ${PROJECT_SOURCE_DIR})
set(MAIN_CPP_SOURCES
    ${MAIN_CPP_DIR}/Disassembler.cpp
)

# add directory of main include files (needed for the test executable)
include_directories(${MAIN_CPP_DIR})

add_executable(prol16-dis-test ${TEST_CPP_SOURCES} ${MAIN_CPP_SOURCES})
target_link_libraries(prol16-dis-test gtest_main prol16shared)
add_test(NAME prol16-dis-test COMMAND prol16-dis-test)

# copy the resource files
add_custom_command(TARGET prol16-dis-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_LIST_DIR}/resources/
            ${CMAKE_CURRENT_BINARY_DIR}/resources/)