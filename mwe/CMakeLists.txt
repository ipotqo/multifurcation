cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    CMAKE_CXX_STANDARD
    20
)

project (
    multifurcation
    VERSION
        0.0.0
    LANGUAGES
        C CXX
)

add_executable ( multifurcation multifurcation.cpp )