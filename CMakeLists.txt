# cmake_minimum_required(VERSION 3.20)

# project(SONOVOLT VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LIB_NAME sonovolt)
set(SONOVOLT_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt)
message(STATUS "Configuring ${LIB_NAME}")
message(STATUS "${LIB_NAME} include path: ${SONOVOLT_INCLUDE}")

# set lib alias
add_library(${LIB_NAME} STATIC)
# add_library(SONOVOLT::sonovolt STATIC ALIAS ${LIB_NAME})

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

# target_compile_definitions(${LIB_NAME} 
#     PRIVATE 
#         PICO_FLOAT_SUPPORT_ROM_V1 = 0
#         PICO_DOUBLE_SUPPORT_ROM_V1 = 0
# )

target_sources(${LIB_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/time/transport.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/math.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/time.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pico/pwm.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pico/output.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pico/tempo_clock.cpp
)

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(${LIB_NAME} 
    PUBLIC
        pico_time
        pico_divider
        pico_printf
        hardware_pwm
        hardware_timer
        hardware_gpio
        pw_function
)

# set(TEST_EXE ${LIB_NAME}_test)

# add_executable(${TEST_EXE} EXCLUDE_FROM_ALL ${CMAKE_CURRENT_LIST_DIR}/test/time.cpp)

# target_compile_features(${TEST_EXE} PRIVATE cxx_std_17)

# find_path(DOCTEST_INCLUDE_DIR NAMES doctest.h PATH_SUFFIXES doctest)
# message(STATUS "doctest include path: ${DOCTEST_INCLUDE_DIR}")
# target_include_directories(${TEST_EXE} 
#     PRIVATE 
#         ${DOCTEST_INCLUDE_DIR}
#         ${CMAKE_CURRENT_LIST_DIR}/include
# )

# target_link_libraries(${TEST_EXE} PRIVATE doctest::doctest)
