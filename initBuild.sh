###############################################################################
## author:      creiterer
## brief:       This script initializes the cmake build.
## usage:       ./initBuild.sh
###############################################################################
#!/bin/bash

readonly PROL16TOOLS_BUILD_DIR="build_prol16-tools"
readonly PROL16TOOLS_SOURCE_DIR="prol16-tools"

# use clang version 7 because ANTLR doesn't compile with clang versions >= 8
readonly C_COMPILER="clang-7"
readonly CPP_COMPILER="clang++-7"
readonly GENERATOR="Ninja"

function buildProl16Tools {
    if [ ! -d "$PROL16TOOLS_BUILD_DIR" ]; then
        echo "Build directory \"${PROL16TOOLS_BUILD_DIR}\" doesn't exist -> initializing prol16-tools cmake build"
        mkdir ${PROL16TOOLS_BUILD_DIR}
        cd ${PROL16TOOLS_BUILD_DIR}
        CC=${C_COMPILER} CXX=${CPP_COMPILER} cmake -G ${GENERATOR} -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "../${PROL16TOOLS_SOURCE_DIR}/"
        ln -sf "${PWD}/compile_commands.json" "../${PROL16TOOLS_SOURCE_DIR}/"
        cd ..
    else
        echo "Build directory \"${PROL16TOOLS_BUILD_DIR}\" exists -> prol16-tools cmake build is already initialized -> nothing to do"
    fi
}

# set up build of prol16-tools
buildProl16Tools
