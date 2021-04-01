#!/bin/bash

make
cp spfind bin/spfind
cd bin
spfind="./spfind"
spfind_expected="./spfind_expected"

#./spfind -d ../../ -p rwxr-xr-x
#exit 0

touch stdout
touch stdout_expected
touch stderr
touch stderr_expected

function normalize_names() {
	sed -i "s|Usage: $spfind|Usage: file_name|g" stdout
	sed -i "s|Usage: $spfind_expected|Usage: file_name|g" stdout_expected
	sed -i "s|Usage: $spfind|Usage: file_name|g" stderr
	sed -i "s|Usage: $spfind_expected|Usage: file_name|g" stderr_expected
}
function check() {
	normalize_names
	diff stderr stderr_expected
	diff stdout stdout_expected
}

echo "TEST 1"
$spfind_expected 2>stderr_expected 1>stdout_expected
$spfind 2>stderr 1>stdout
check

echo "TEST 2"
$spfind_expected -d ~ -p rwxr-xr-q 2>stderr_expected 1>stdout_expected
$spfind -d ~ -p rwxr-xr-q 2>stderr 1>stdout
check

echo "TEST 3"
$spfind_expected -d .. -p rwxr-xr-x 2>stderr_expected 1>stdout_expected
$spfind -d .. -p rwxr-xr-x 2>stderr 1>stdout
check
echo "TEST 4"
#$spfind_expected -d ~ -p rw-r-xr-x 2>stderr_expected 1>stdout_expected
#$spfind -d ~ -p rw-r-xr-x 2>stderr 1>stdout
#check
rm stdout
rm stdout_expected
rm stderr
rm stderr_expected
