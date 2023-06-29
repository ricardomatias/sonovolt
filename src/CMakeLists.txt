set(LIB_NAME sonovolt)

# set lib alias
add_library(${LIB_NAME} STATIC)

# add_library(SONOVOLT::sonovolt STATIC ALIAS ${LIB_NAME})
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

# target_compile_definitions(${LIB_NAME}
# PRIVATE
# PICO_FLOAT_SUPPORT_ROM_V1 = 0
# PICO_DOUBLE_SUPPORT_ROM_V1 = 0
# )
if(SONOVOLT_TOP_LEVEL)
    target_sources(${LIB_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/time/transport.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/common/math.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/common/time.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/time/transport.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/time/timeline.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/common/math.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/common/time.h
    )

    target_include_directories(${LIB_NAME}
        PRIVATE

        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    )

    include(ExternalProject)

    ExternalProject_Add(sonovolt-pico
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/pico"
        INSTALL_DIR "${installDir}"

        # INSTALL_COMMAND ""
        DOWNLOAD_COMMAND ""
        BUILD_ALWAYS YES
        CMAKE_ARGS
        -DCMAKE_TOOLCHAIN_FILE=$ENV{PICO_SDK_PATH}/cmake/preload/toolchains/pico_arm_gcc.cmake
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
        -DSONOVOLT_TOP_LEVEL=${SONOVOLT_TOP_LEVEL}
    )
else()
    target_sources(${LIB_NAME}
        PRIVATE

        ${CMAKE_CURRENT_SOURCE_DIR}/common/math.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/common/time.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/time/transport.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/time/transport.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/time/timeline.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/common/math.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/common/time.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/sonovolt/types.h
    )
    target_include_directories(${LIB_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    )

# target_link_libraries(${LIB_NAME}
# PUBLIC
# # pico_time
# # pico_divider
# # pico_printf
# # hardware_pwm
# # hardware_timer
# # hardware_gpio
# )
endif()
