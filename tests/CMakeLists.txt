# cmake_minimum_required(VERSION 3.26)

# project(sonovolt_tests CXX C)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY "https://github.com/doctest/doctest.git"
    GIT_TAG "v2.4.11"
)

FetchContent_MakeAvailable(doctest)

enable_testing()

add_executable(tests time.cpp)
target_compile_features(tests PRIVATE cxx_std_17)
# target_link_libraries(tests doctest sonovolt)
# target_include_directories(tests PRIVATE ${doctest_INCLUDE_DIR})
target_link_libraries(tests doctest sonovolt)

include(CTest)
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(tests)

# add_executable(${PROJECT_NAME} EXCLUDE_FROM_ALL ${CMAKE_CURRENT_LIST_DIR}/time.cpp)

# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)

# include(CTest)
# include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
