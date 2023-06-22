set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(sonovolt_daisy STATIC)

target_compile_features(sonovolt_daisy PRIVATE cxx_std_17)

target_sources(sonovolt_daisy PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/tempo_sampler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/file_utils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sdram.cpp
)

target_include_directories(sonovolt_daisy PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in daisy libraries that we need
target_link_libraries(sonovolt_daisy PRIVATE sonovolt daisy)