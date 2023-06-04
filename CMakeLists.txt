cmake_minimum_required(VERSION 3.26)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(SONOVOLT_TOP_LEVEL ON)
endif()

set(installDir "${CMAKE_CURRENT_BINARY_DIR}/install")

OPTION(DEBUG_BUILD "Build for Debug binary" ON)

# if(DEBUG_BUILD)
# endif()
project(SONOVOLT VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# if(DEBUG_BUILD)
add_subdirectory(src)

if(SONOVOLT_TOP_LEVEL)
    add_subdirectory(tests)
endif()

# else()
# add_subdirectory(src)

# enable_testing()
# add_subdirectory(tests)
# include(ExternalProject)

# ExternalProject_Add(sonovolt-tests
# SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/tests"
# INSTALL_DIR "${installDir}"
# INSTALL_COMMAND ""
# DOWNLOAD_COMMAND ""
# BUILD_ALWAYS YES
# CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/cmake/i686-w64-mingw32.cmake
# -DCMAKE_BUILD_TYPE=${CMAKE_DEFAULT_BUILD_TYPE}
# -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
# )
# endif()
