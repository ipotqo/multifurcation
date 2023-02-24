cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    CMAKE_CXX_STANDARD
    20
)

set (
    PROJECT_NAME
    tool_lib
)

set (
    LIBRARY_NAME
    tool
)

set (
    LIBRARY_HEADERS_DIR
    include/${LIBRARY_NAME}
)

set (
    LIBRARY_HEADERS
    ${LIBRARY_HEADERS_DIR}/tool.hpp
)

set (
    LIBRARY_SOURCE_DIR
    src
)

set (
    LIBRARY_SOURCE
    ${LIBRARY_SOURCE_DIR}/tool.cpp
)

set (
    MULTIFURCATION_UTILITIES
    utl
    author
)

project (
    ${PROJECT_NAME}
    VERSION
        0.0.0
    DESCRIPTION
        "Tailored Toolkit"
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

target_link_libraries (
    tool PUBLIC
    ${MULTIFURCATION_UTILITIES}
)

add_subdirectory ( test )