cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    CMAKE_CXX_STANDARD
    20
)

set (
    PROJECT_NAME
    utl_lib
)

set (
    LIBRARY_NAME
    utl
)

set (
    LIBRARY_HEADERS_DIR
    include/${LIBRARY_NAME}
)

set (
    LIBRARY_HEADERS
    ${LIBRARY_HEADERS_DIR}/utl.hpp
)

set (
    LIBRARY_SOURCE_DIR
    src
)

set (
    LIBRARY_SOURCE
    ${LIBRARY_SOURCE_DIR}/utl.cpp
)

project (
    ${PROJECT_NAME}
    VERSION
        0.0.0
    DESCRIPTION
        "General Utilities Suite"
    LANGUAGES
        C CXX
)

add_library (
    ${LIBRARY_NAME} STATIC
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCE}
)

target_include_directories (
    ${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

target_include_directories (
    ${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory ( test )