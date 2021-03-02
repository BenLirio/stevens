#!/bin/bash
clear
make
echo
echo STRINGS
./sort testdata/strings
echo
echo INTS
./sort -i testdata/ints
echo
echo DOUBLES
./sort -d testdata/doubles
