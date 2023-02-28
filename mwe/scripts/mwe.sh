#!/usr/bin/zsh

cmake -S . -B build
cmake --build build
cmake --build build --target test
# cmake --build build --target doc

cd build/multifurcation
make
./multifurcation