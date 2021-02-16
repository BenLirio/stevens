#!/bin/bash

LOGS_FILE=./.logs
EXPECTED_OUTPUT=./.expected_output

let i=1
check (){
	echo -e "\n\nOUTPUT ${i}"
	diff "${LOGS_FILE}" "${EXPECTED_OUTPUT}"
	i=$(( i + 1 ))
}
clean ()
{
	if [[ -e ./.junk ]]; then rm -r ./.junk; fi
	if [[ -e ./dir1 ]]; then rm -r ./dir1; fi
	if [[ -e ./dir2 ]]; then rm -r ./dir2; fi
	if [[ -e ./.hideme ]]; then rm -r ./.hideme; fi
	if [[ -e ./junk0.txt ]]; then rm -r ./junk0.txt; fi
	if [[ -e ./logs ]]; then rm -r ./logs; fi
}
clean


touch junk0.txt
mkdir -p dir1
mkdir -p dir2/dir3
mkdir .hideme
touch dir1/junk1.txt
touch dir2/junk2.txt
touch dir2/dir3/junk3.txt

find . -print0 | while IFS= read -r -d '' file
do
	touch -d 'Jan 1 2020' "${file}"
done


# Created Proper files
tree > $LOGS_FILE
cat << EOF > "${EXPECTED_OUTPUT}"
.
|-- dir1
|   \`-- junk1.txt
|-- dir2
|   |-- dir3
|   |   \`-- junk3.txt
|   \`-- junk2.txt
|-- junk.sh
|-- junk0.txt
\`-- test.sh

3 directories, 6 files
EOF
check


./junk.sh junk0.txt > $LOGS_FILE
cat << EOF > "${EXPECTED_OUTPUT}"

EOF
check


./junk.sh -l > $LOGS_FILE
cat << EOF > "${EXPECTED_OUTPUT}"
-rw-rw-r-- 1 user user 0 Jan 1 2000 junk0.txt
EOF
check

./junk.sh dir2/dir3/junk3.txt > $LOGS_FILE
cat << EOF > "${EXPECTED_OUTPUT}"
-rw-rw-r-- 1 user user 0 Jan 1 2000 junk0.txt
EOF
check
./junk.sh .hideme > $LOGS_FILE
./junk.sh -l > $LOGS_FILE
tree > $LOGS_FILE
tree -a ./.junk > $LOGS_FILE
./junk.sh -p > $LOGS_FILE
./junk.sh -l > $LOGS_FILE
tree -a ./.junk > $LOGS_FILE

clean

exit 0
