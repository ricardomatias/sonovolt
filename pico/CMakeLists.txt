# if (NOT TARGET sonovolt_pico)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(MAKE_EXPORT_COMPILE_COMMANDS ON)

set(LIB_NAME sonovolt_pico)
add_library(${LIB_NAME} INTERFACE)

target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_SOURCE_DIR}/include)

target_sources(${LIB_NAME} INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/pico.cpp
)

target_link_libraries(${LIB_NAME} INTERFACE hardware_pwm)
# endif()


