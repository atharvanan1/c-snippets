#! /bin/bash

set -e

cd `dirname $0`
if [ -d build ]; then
    if grep -Fxq "BUILD_TEST:BOOL=OFF" build/CMakeCache.txt; then
        rm -rf build
    fi
fi
cmake -S . -B build -D BUILD_TEST=ON
cmake --build build
pushd build
ctest $@
popd
