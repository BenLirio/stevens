#!/bin/bash
clear
make
echo "./sort"
./sort
echo
echo
echo
echo "./sort -z"
./sort -z
echo
echo
echo
echo "./sort -d notfound.txt"
./sort -d notfound.txt
echo
echo
echo
echo "./sort -i"
./sort -i
echo
echo
echo
echo "./sort -id"
./sort -id
echo
echo
echo
echo "./sort possible.txt ohno.txt"
./sort possible.txt ohno.txt
echo
echo
echo
echo "./sort -iz ints.txt"
./sort -iz ints.txt
