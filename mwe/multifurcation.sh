#!/usr/bin/zsh

build_dir=build
main_exe=multifurcation

mkdir $build_dir
cd $build_dir
cmake ..
make

./$main_exe