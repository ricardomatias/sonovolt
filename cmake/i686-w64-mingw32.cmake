# Define the environment for cross-compiling with 32-bit MinGW-w64 GCC
set(CMAKE_SYSTEM_NAME Windows) # Target system name
# set(WIN32 TRUE)
set(CMAKE_SYSTEM_PROCESSOR i686) # Target processor name

# set(CMAKE_SYSTEM_VERSION 1)
set(MINGW32_PATH "C:/Users/Ricardo/scoop/apps/mingw-winlibs-llvm-ucrt-x86/current")
set(MINGW32_BIN_PATH "${MINGW32_PATH}/bin")
set(MINGW32_LIB_PATH "${MINGW32_PATH}/lib")
list(APPEND CMAKE_PROGRAM_PATH "${MINGW32_BIN_PATH}")

set(CMAKE_CXX_COMPILE_OPTIONS_SYSROOT "--sysroot=")
set(CMAKE_SYSROOT ${MINGW32_LIB_PATH})

# set(CMAKE_MAKE_PROGRAM "${MINGW32_PATH}/make.exe")
set(CMAKE_C_COMPILER "${MINGW32_BIN_PATH}/i686-w64-mingw32-gcc.exe")
set(CMAKE_CXX_COMPILER "${MINGW32_BIN_PATH}/i686-w64-mingw32-g++.exe")
set(CMAKE_CXX_COMPILER_AR "${MINGW32_BIN_PATH}/i686-w64-mingw32-gcc-ar.exe")
set(CMAKE_RC_COMPILER "${MINGW32_BIN_PATH}/windres.exe")
set(CMAKE_RANLIB "${MINGW32_BIN_PATH}/i686-w64-mingw32-gcc-ranlib.exe")
set(CMAKE_LINKER "${MINGW32_BIN_PATH}/ld.exe")

# Configure the behaviour of the find commands
set(CMAKE_FIND_ROOT_PATH "${MINGW32_PATH}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
