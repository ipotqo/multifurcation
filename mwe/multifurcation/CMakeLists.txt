add_executable( multifurcation multifurcation.cpp )

target_compile_features( multifurcation PRIVATE cxx_std_20 )

target_link_libraries( multifurcation PRIVATE mwe_lib fmt::fmt )
