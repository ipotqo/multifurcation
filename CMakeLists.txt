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

# HEADERS

set (
    MULTIFURCATION_HEADERS_DIR
    include/${MULTIFURCATION_LIBRARY_NAME}
)

set (
    MULTIFURCATION_HEADERS
    ${MULTIFURCATION_HEADERS_DIR}/multifurcation.hpp
)

# SOURCE

set (
    MULTIFURCATION_SOURCE_DIR
    src
)

set (
    MULTIFURCATION_SOURCE
    ${MULTIFURCATION_SOURCE_DIR}/multifurcation.cpp
)

# LIBRARIES
set (
    MULTIFURCATION_LIBRARIES_DIR
    lib
)

set (
    MULTIFURCATION_LIBRARIES
    innovator
    inventor
)

# TOOLS

set (
    MULTIFURCATION_TOOLS_DIR
    tools
)

set (
    MULTIFURCATION_TOOLS
    academic
    # artisan
    tool
)

# UTILITIES

set (
    MULTIFURCATION_UTILITIES_DIR
    utilities
)

set (
    MULTIFURCATION_UTILITIES
    # artist
    author
    utl
)

# PROJECT

project (
    multifurcation
    VERSION
        0.0.0
    DESCRIPTION
        "CMake Structure with Branched Subdivisions"
    LANGUAGES
        C CXX
)

enable_testing ()
add_subdirectory ( external/googletest )
include_directories (
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
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

foreach ( UTILITY ${MULTIFURCATION_UTILITIES} )
    add_subdirectory ( ${MULTIFURCATION_UTILITIES_DIR}/${UTILITY} )
endforeach ( UTILITY ${MULTIFURCATION_UTILITIES} )

foreach ( TOOL ${MULTIFURCATION_TOOLS} )
    add_subdirectory ( ${MULTIFURCATION_TOOLS_DIR}/${TOOL} )
endforeach ( TOOL ${MULTIFURCATION_TOOLS} )

foreach ( LIBRARY ${MULTIFURCATION_LIBRARIES} )
    add_subdirectory ( ${MULTIFURCATION_LIBRARIES_DIR}/${LIBRARY} )
endforeach ( LIBRARY ${MULTIFURCATION_LIBRARIES} )

add_subdirectory ( test )

target_link_libraries (
    ${MULTIFURCATION_PROJECT_NAME}
    ${MULTIFURCATION_UTILITIES}
    ${MULTIFURCATION_TOOLS}
    ${MULTIFURCATION_LIBRARIES}
)