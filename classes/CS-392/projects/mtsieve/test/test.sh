#!/bin/bash

T=0
S=0
E=0
fail() {
	echo -s $S -e $E -t $T
	echo LOGS:
	cat logs
	echo MY LOGS:
	cat my_logs
	echo ERRS:
	cat errs
	echo MY_ERRS:
	cat my_errs
	exit
}
./mtsieve 1>logs 2>errs
./my_mtsieve 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -s 3 1>logs 2>errs
./my_mtsieve -s 3 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -e 3 1>logs 2>errs
./my_mtsieve -e 3 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -t 3 1>logs 2>errs
./my_mtsieve -t 3 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -s 3 -t 3 1>logs 2>errs
./my_mtsieve -s 3 -t 3 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -s 3 -t 3 -e 100 1>logs 2>errs
./my_mtsieve -s 3 -t 3 -e 100 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve asdf 1>logs 2>errs
./my_mtsieve asdf 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -s 123 asdf 1>logs 2>errs
./my_mtsieve -s 123 asdf 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -s 123 -e asdf 1>logs 2>errs
./my_mtsieve -s 123 -e asdf 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -s 123 -t -1 1>logs 2>errs
./my_mtsieve -s 123 -t -1 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -s 2 -e 4294967296 -t -32 1>logs 2>errs
./my_mtsieve -s 2 -e 4294967296 -t -32 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
./mtsieve -s 2 -e 4294967297 -t -32 1>logs 2>errs
./my_mtsieve -s 2 -e 4294967297 -t -32 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
for i in `seq 2 10000 100000`
do
echo $i
./mtsieve -s 2 -e $i -t -32 1>logs 2>errs
./my_mtsieve -s 2 -e $i -t -32 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
done
while true
do
t=$((-4 + $RANDOM % 40))
s=$(($RANDOM))
e=$(($RANDOM))
echo [$s-$e] t=$t
T=$t
S=$s
E=$e
./mtsieve -s $s -e $e -t $t 1>logs 2>errs
./my_mtsieve -s $s -e $e -t $t 1>my_logs 2>my_errs
diff logs my_logs || fail
diff errs my_errs || fail
done
