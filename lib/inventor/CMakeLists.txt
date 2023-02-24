cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    CMAKE_CXX_STANDARD
    20
)

set (
    PROJECT_NAME
    inventor_lib
)

set (
    LIBRARY_NAME
    inventor
)

set (
    LIBRARY_HEADERS_DIR
    include/${LIBRARY_NAME}
)

set (
    LIBRARY_HEADERS
    ${LIBRARY_HEADERS_DIR}/inventor.hpp
)

set (
    LIBRARY_SOURCE_DIR
    src
)

set (
    LIBRARY_SOURCE
    ${LIBRARY_SOURCE_DIR}/inventor.cpp
)

set (
    MULTIFURCATION_UTILITIES
    utl
    author
)

set (
    MULTIFURCATION_TOOLS
    tool
    academic
)

project (
    ${PROJECT_NAME}
    VERSION
        0.0.0
    DESCRIPTION
        "Internal Libraries"
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
    inventor PUBLIC
    ${MULTIFURCATION_UTILITIES}
    ${MULTIFURCATION_TOOLS}
)

add_subdirectory ( test )