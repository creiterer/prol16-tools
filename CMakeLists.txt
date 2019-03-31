CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

#### GENERAL SETUP ####

# use c++14
set(CMAKE_CXX_STANDARD 14)

set(WARNING_FLAGS "-Wall -Wnon-virtual-dtor -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")

set(CLANG_FLAGS "-Xclang -fcolor-diagnostics")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_FLAGS}")
endif()

#### GTEST SETUP ####

# download and unpack googletest at configure time
configure_file(${PROJECT_SOURCE_DIR}/thirdparty/googletest/CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)             

#### TARGET SETUP ####

add_subdirectory(prol16-shared)
add_subdirectory(prol16-as)
add_subdirectory(prol16-dis)
add_subdirectory(prol16-vm)

