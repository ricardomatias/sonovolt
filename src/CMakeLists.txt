set(LIB_NAME sonovolt)
set(BASE_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/../include/${LIB_NAME})

add_library(
    ${LIB_NAME}
    STATIC
    # Headers
    ${BASE_INCLUDE}/common/math.h
    ${BASE_INCLUDE}/common/time.h
    ${BASE_INCLUDE}/pico.h

    # Sources
    ${PROJECT_SOURCE_DIR}/src/common/math.cpp
    ${PROJECT_SOURCE_DIR}/src/common/time.cpp
    ${PROJECT_SOURCE_DIR}/src/pico/pico.cpp
)

add_library(sonovolt::sonovolt ALIAS ${LIB_NAME})

target_compile_features(${LIB_NAME} PUBLIC cxx_std_20)

target_include_directories(${LIB_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include/>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIB_NAME} hardware_pwm)

