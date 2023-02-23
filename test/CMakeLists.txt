cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    PROJECT_TEST_NAME
    multifurcation_test
)

set (
    PROJECT_TEST_SOURCE
    multifurcation_test.cpp
)

project ( ${PROJECT_TEST_NAME} )

enable_testing ()

if ( NOT ( TARGET gtest AND TARGET gtest_main ) )
    message ( FATAL_ERROR "Missing Targets: gtest and gtest_main" )
endif ()

add_executable (
    ${PROJECT_TEST_NAME}
    ${PROJECT_TEST_SOURCE}
)

target_link_libraries (
    ${PROJECT_TEST_NAME}
    gtest
    gtest_main
    ${LIBRARY_NAME}
)

add_test (
    ${PROJECT_TEST_NAME}
    ${PROJECT_TEST_NAME}
)