#!/bin/bash

mkdir -p build 

pushd build
cmake ../
VERBOSE=1 cmake --build . --parallel
popd
