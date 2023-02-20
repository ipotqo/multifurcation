cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    CMAKE_CXX_STANDARD
    20
)

set (
    MULTIFURCATION_PROJECT_NAME
    "multifurcation"
)

set (
    MULTIFURCATION_LIBRARY_NAME
    multifurcation
)

set (
    MULTIFURCATION_HEADERS_DIR
    include/${MULTIFURCATION_LIBRARY_NAME}
)

set (
    MULTIFURCATION_HEADERS
    ${MULTIFURCATION_HEADERS_DIR}/multifurcation.hpp
)

set (
    MULTIFURCATION_SOURCE_DIR
    src
)

set (
    MULTIFURCATION_SOURCE
    ${MULTIFURCATION_SOURCE_DIR}/multifurcation.cpp
)

project (
    multifurcation
    VERSION
        0.0.0
    DESCRIPTION
        "CMake Structure with Branched Subdivisions"
    LANGUAGES
        C CXX
)

add_executable (
    ${MULTIFURCATION_PROJECT_NAME}
    ${MULTIFURCATION_SOURCE}
)

target_include_directories (
    ${MULTIFURCATION_LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${MULTIFURCATION_LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${MULTIFURCATION_LIBRARY_NAME}>
)

target_include_directories (
    ${MULTIFURCATION_LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include>
)