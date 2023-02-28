cmake_minimum_required ( VERSION 3.14...3.25 )

set (
  CMAKE_CXX_STANDARD
  20
)

project (
  mwe
  VERSION
    0.0.0
  DESCRIPTION
    "mwe"
  LANGUAGES
    C CXX
)

if (
  CMAKE_PROJECT_NAME
  STREQUAL
  PROJECT_NAME
)

set (
  CMAKE_CXX_EXTENSIONS OFF
)

set_property ( GLOBAL PROPERTY USE_FOLDERS ON )

include( CTest )

find_package( Doxygen )
  if ( Doxygen_FOUND )
    add_subdirectory( doc )
  else ()
    message( STATUS "Doxygen not found so documentation will not be built" )
  endif ()
endif ()

include( FetchContent )

find_package( Boost REQUIRED )

FetchContent_Declare (
  fmtlib
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 5.3.0 )
FetchContent_MakeAvailable( fmtlib )

add_subdirectory( src )

add_subdirectory( multifurcation )

if(
  ( CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING )
   AND BUILD_TESTING )
  add_subdirectory( test )
endif ()