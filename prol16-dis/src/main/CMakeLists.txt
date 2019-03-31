#### TARGET SETUP ####

get_filename_component(MAIN_CPP_DIR "cpp/" ABSOLUTE)
set(MAIN_CPP_SOURCES
    ${MAIN_CPP_DIR}/main.cpp
    ${MAIN_CPP_DIR}/Disassembler.cpp
    ${MAIN_CPP_DIR}/CLIArguments.cpp
)

add_executable(prol16-dis ${MAIN_CPP_SOURCES})
target_link_libraries(prol16-dis prol16shared)