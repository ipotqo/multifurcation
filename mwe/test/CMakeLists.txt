FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)

add_executable( mwe_test mwe_test.cpp )

target_compile_features( mwe_test PRIVATE cxx_std_20 )

target_link_libraries( mwe_test PRIVATE mwe_lib Catch2::Catch2 )

add_test(NAME mwe_lib_test COMMAND mwe_test )
