#!/bin/bash
LOGS_FILE=./logs
rm -r ./.junk
rm -r ./dir1
rm -r ./dir2
rm -r ./.hideme
rm junk0.txt

touch junk0.txt
mkdir -p dir1
mkdir -p dir2/dir3
mkdir .hideme
touch dir1/junk1.txt
touch dir2/junk2.txt
touch dir2/dir3/junk3.txt
tree > $LOGS_FILE

./junk.sh junk0.txt > $LOGS_FILE
./junk.sh -l > $LOGS_FILE
./junk.sh dir2/dir3/junk3.txt > $LOGS_FILE
./junk.sh .hideme > $LOGS_FILE
./junk.sh -l > $LOGS_FILE
tree > $LOGS_FILE
tree -a ./.junk > $LOGS_FILE
./junk.sh -p > $LOGS_FILE
./junk.sh -l > $LOGS_FILE
tree -a ./.junk > $LOGS_FILE
exit 0
