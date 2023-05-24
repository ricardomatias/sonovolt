# cmake_minimum_required(VERSION 3.26)

# project(
#     sonovolt 
#     VERSION 0.1
#     LANGUAGES CXX C ASM
# )

set(MAKE_EXPORT_COMPILE_COMMANDS ON)

set(LIB_NAME sonovolt)
message(STATUS "Configuring ${LIB_NAME}")
set(SONOVOLT_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt)
message(STATUS "INCLUDE: ${SONOVOLT_INCLUDE}")

add_library( ${LIB_NAME} STATIC)

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

target_sources(${LIB_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/common/math.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/common/time.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/pico/pico.cpp
)

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(${LIB_NAME} PUBLIC hardware_pwm)


# set(MAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# # Let's ensure -std=c++xx instead of -std=g++xx
# set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_CXX_VISIBILITY_PRESET hidden)
# set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)


# add_library(sonovolt::sonovolt ALIAS ${LIB_NAME})

# set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

# add_library(
#     ${LIB_NAME}
#     STATIC
#     # Headers
#     ${BASE_INCLUDE}/common/math.h
#     ${BASE_INCLUDE}/common/time.h
#     ${BASE_INCLUDE}/pico.h

#     # Sources
#     ${CMAKE_CURRENT_LIST_DIR}/src/common/math.cpp
#     ${CMAKE_CURRENT_LIST_DIR}/src/common/time.cpp
#     ${CMAKE_CURRENT_LIST_DIR}/src/pico/pico.cpp
# )