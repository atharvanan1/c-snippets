#! /bin/bash

set -e

cd `dirname $0`
cmake -S . -B build -D BUILD_TEST=OFF
cmake --build build
./build/src/Dummy
