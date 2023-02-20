#!/usr/bin/zsh

build_dir=build

mkdir $build_dir
cd $build_dir
cmake ..
make