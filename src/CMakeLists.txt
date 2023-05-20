set(LIB_NAME sonovolt)
set(BASE_INCLUDE ${CMAKE_SOURCE_DIR}/include/${LIB_NAME})

add_library(
    ${LIB_NAME}
    # Headers
    ${BASE_INCLUDE}/common/math.h
    ${BASE_INCLUDE}/common/time.h

    # Sources
    ${PROJECT_SOURCE_DIR}/src/common/math.cpp
    ${PROJECT_SOURCE_DIR}/src/common/time.cpp
)

add_library(sonovolt::sonovolt ALIAS ${LIB_NAME})
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include(GenerateExportHeader)
generate_export_header(${LIB_NAME}
    EXPORT_MACRO_NAME SONOVOLT_API
    EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/${LIB_NAME}/${LIB_NAME}.h
)

target_compile_features(${LIB_NAME} PUBLIC cxx_std_20)

target_include_directories(${LIB_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(${LIB_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME})

install(TARGETS ${LIB_NAME}
    EXPORT ${LIB_NAME}-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/${LIB_NAME}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/include/${LIB_NAME}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${LIB_NAME}-targets
    FILE ${LIB_NAME}-targets.cmake
    NAMESPACE ${LIB_NAME}::
    DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${LIB_NAME}-config-version.cmake
    VERSION ${${LIB_NAME}_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/${LIB_NAME}-config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/${LIB_NAME}-config.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
    FILES
        ${CMAKE_BINARY_DIR}/cmake/${LIB_NAME}-config.cmake
        ${CMAKE_BINARY_DIR}/cmake/${LIB_NAME}-config-version.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT ${LIB_NAME}-targets
    FILE ${CMAKE_BINARY_DIR}/cmake/${LIB_NAME}-targets.cmake
    NAMESPACE ${LIB_NAME}::
)

export(PACKAGE ${LIB_NAME})