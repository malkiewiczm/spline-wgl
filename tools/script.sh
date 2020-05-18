#!/bin/sh
test -z "$1" && echo 'no argument given' && exit
./obj_to_bin.exe "$1.obj" "$1.bin" && ./bin_to_cpp.exe "$1.bin" "../src/$1_obj.cpp" "g::obj::$1"
