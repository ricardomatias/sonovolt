add_library(sonovolt_daisy INTERFACE)

target_sources(sonovolt_daisy INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/tempo_sampler.cpp
)

target_include_directories(sonovolt_daisy INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in daisy libraries that we need
target_link_libraries(sonovolt_daisy INTERFACE sonovolt)