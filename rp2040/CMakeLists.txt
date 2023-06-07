add_library(sonovolt_pico INTERFACE)

target_sources(sonovolt_pico INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/output.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pwm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tempo_clock.cpp
)

target_include_directories(sonovolt_pico INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in pico libraries that we need
target_link_libraries(sonovolt_pico INTERFACE pico_stdlib sonovolt)