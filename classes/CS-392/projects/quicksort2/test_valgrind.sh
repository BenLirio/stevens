#!/bin/bash
clear
make
echo
echo STRINGS
valgrind ./sort testdata/strings
echo
echo INTS
valgrind ./sort -i testdata/ints
echo
echo DOUBLES
valgrind ./sort -d testdata/doubles
