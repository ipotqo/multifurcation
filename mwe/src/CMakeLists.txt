set (
  HEADER_LIST
  "${mwe_SOURCE_DIR}/include/mwe/mwe.hpp"
  "${mwe_SOURCE_DIR}/include/mwe/location.hpp"
)

add_library ( mwe_lib mwe.cpp location.cpp ${HEADER_LIST} )

target_include_directories ( mwe_lib PUBLIC ../include )

target_link_libraries ( mwe_lib PRIVATE Boost::boost )

target_compile_features ( mwe_lib PUBLIC cxx_std_20 )

source_group (
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)