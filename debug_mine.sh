#!/bin/sh
clang -Iincludes -L. -lft_malloc test$1.c -o test$1_mine
export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH

echo "===With /usr/bin/time==="
/usr/bin/time -v ./test$1_mine

echo "===With valgrind==="
valgrind ./test$1_mine

echo "===Raw==="
./test$1_mine
