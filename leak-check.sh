#! /bin/bash

cd `dirname $0`
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=build/valgrind-out.txt \
         ./build/src/Dummy
