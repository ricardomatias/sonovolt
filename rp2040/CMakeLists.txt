add_library(sonovolt_pico INTERFACE)

target_sources(sonovolt_pico INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/output.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gate_in.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pwm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tempo_clock.cpp
    ${CMAKE_CURRENT_LIST_DIR}/debounce.cpp
    ${CMAKE_CURRENT_LIST_DIR}/encoder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/switch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/toggle3.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/max7219.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pico7219.cpp

    # ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt/rp2040/time.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt/rp2040/debounce.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt/rp2040/gpio.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt/rp2040/knob.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt/rp2040/button.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt/rp2040/output.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt/rp2040/pwm.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/sonovolt/rp2040/tempo_clock.h
)

target_include_directories(sonovolt_pico INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in pico libraries that we need
target_link_libraries(sonovolt_pico INTERFACE pico_stdlib pico_rand hardware_pio hardware_dma hardware_spi sonovolt)

pico_generate_pio_header(sonovolt_pico ${CMAKE_CURRENT_LIST_DIR}/debounce.pio)
pico_generate_pio_header(sonovolt_pico ${CMAKE_CURRENT_LIST_DIR}/encoder.pio)