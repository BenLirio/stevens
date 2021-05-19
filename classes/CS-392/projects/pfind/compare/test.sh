#!/bin/bash

# Test 1
echo "TEST 1"
valgrind ./pfind -h 2>error_logs 1>logs
rtn=$?
valgrind ./mypfind -h 2>my_error_logs 1>my_logs
my_rtn=$?
if [[ rtn -ne my_rtn ]]
then
	echo "Expected mypfind to return ${rtn} got ${my_rtn}"
fi
sed -i s/mypfind/pfind/g my_logs
sed -i s/mypfind/pfind/g my_error_logs
diff error_logs my_error_logs
diff logs my_logs

# Test 2
echo "TEST 2"
valgrind ./pfind -v -h 2>error_logs 1>logs
rtn=$?
valgrind ./mypfind -v -h 2>my_error_logs 1>my_logs
my_rtn=$?
if [[ rtn -ne my_rtn ]]
then
	echo "Expected mypfind to return ${rtn} got ${my_rtn}"
fi
sed -i s/mypfind/pfind/g my_logs
sed -i s/mypfind/pfind/g my_error_logs
diff error_logs my_error_logs
diff logs my_logs

# Test 3
echo "TEST 3"
valgrind ./pfind -d test_dir 2>error_logs 1>logs
rtn=$?
valgrind ./mypfind -d test_dir 2>my_error_logs 1>my_logs
my_rtn=$?
if [[ rtn -ne my_rtn ]]
then
	echo "Expected mypfind to return ${rtn} got ${my_rtn}"
fi
sed -i s/mypfind/pfind/g my_logs
sed -i s/mypfind/pfind/g my_error_logs
diff error_logs my_error_logs
diff logs my_logs

# Test 4
echo "TEST 4"
valgrind ./pfind -p rwxrwxrwx 2>error_logs 1>logs
rtn=$?
valgrind ./mypfind -p rwxrwxrwx 2>my_error_logs 1>my_logs
my_rtn=$?
if [[ rtn -ne my_rtn ]]
then
	echo "Expected mypfind to return ${rtn} got ${my_rtn}"
fi
sed -i s/mypfind/pfind/g my_logs
sed -i s/mypfind/pfind/g my_error_logs
diff error_logs my_error_logs
diff logs my_logs

# Test 5
echo "TEST 5"
valgrind ./pfind -d test_dir -p badpermis 2>error_logs 1>logs
rtn=$?
valgrind ./mypfind -d test_dir -p badpermis 2>my_error_logs 1>my_logs
my_rtn=$?
if [[ rtn -ne my_rtn ]]
then
	echo "Expected mypfind to return ${rtn} got ${my_rtn}"
fi
sed -i s/mypfind/pfind/g my_logs
sed -i s/mypfind/pfind/g my_error_logs
diff error_logs my_error_logs
diff logs my_logs


# Test 6
echo "TEST 6"
valgrind ./pfind -d test_dir -p rwxrwxrwx -h 2>error_logs 1>logs
rtn=$?
valgrind ./mypfind -d test_dir -p rwxrwxrwx -h 2>my_error_logs 1>my_logs
my_rtn=$?
if [[ rtn -ne my_rtn ]]
then
	echo "Expected mypfind to return ${rtn} got ${my_rtn}"
fi
sed -i s/mypfind/pfind/g my_logs
sed -i s/mypfind/pfind/g my_error_logs
diff error_logs my_error_logs
diff logs my_logs

# Test 7
echo "TEST 7"
valgrind ./pfind -d test_dir -p rw-r--r-- 2>error_logs 1>logs
rtn=$?
valgrind ./mypfind -d test_dir -p rw-r--r-- 2>my_error_logs 1>my_logs
my_rtn=$?
if [[ rtn -ne my_rtn ]]
then
	echo "Expected mypfind to return ${rtn} got ${my_rtn}"
fi
sed -i s/mypfind/pfind/g my_logs
sed -i s/mypfind/pfind/g my_error_logs
diff error_logs my_error_logs
diff logs my_logs

# Test 8
echo "TEST 8"
valgrind ./pfind -d test_dir -p --x--x--x 2>error_logs 1>logs
rtn=$?
valgrind ./mypfind -d test_dir -p --x--x--x 2>my_error_logs 1>my_logs
my_rtn=$?
if [[ rtn -ne my_rtn ]]
then
	echo "Expected mypfind to return ${rtn} got ${my_rtn}"
fi
sed -i s/mypfind/pfind/g my_logs
sed -i s/mypfind/pfind/g my_error_logs
diff error_logs my_error_logs
diff logs my_logs
