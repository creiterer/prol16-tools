#### TARGET SETUP ####

get_filename_component(MAIN_CPP_DIR "cpp/" ABSOLUTE)
set(MAIN_CPP_SOURCES
    ${MAIN_CPP_DIR}/main.cpp
    ${MAIN_CPP_DIR}/AddressRange.cpp
    ${MAIN_CPP_DIR}/Prol16.cpp
    ${MAIN_CPP_DIR}/VirtualHmiDevice.cpp
    ${MAIN_CPP_DIR}/VirtualMachine.cpp
    ${MAIN_CPP_DIR}/VirtualMemory.cpp
)

add_executable(prol16-vm ${MAIN_CPP_SOURCES})
target_link_libraries(prol16-vm prol16shared)