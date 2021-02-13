#!/bin/bash

let HELP_FLAG=2**0
let LIST_FLAG=2**1
let PURGE_FLAG=2**2
JUNK_FOLDER="./.junk"

usage ()
{
# ---- begin here document ---- #
	cat << EOF
Usage: junk.sh [-hlp] [list of files]
	-h: Display help
	-l: List junked files.
	-p: Purge all files.
	[list of files] with no other arguments to junk those files.
EOF
# ---- end here document ---- #
	exit 0
}

flag=0

check_num_flags ()
{
	if [[ ! flag -eq 0 ]]
	then
		echo "Error: Too many options enabled." >&2
		usage
	fi
}

while getopts ":h :l :p" opt; do
	case ${opt} in
		h) check_num_flags
		   flag=$((flag + HELP_FLAG))
			;;
		l) check_num_flags
		   flag=$((flag + LIST_FLAG))
			;;
		p) check_num_flags
		   flag=$((flag + PURGE_FLAG))
			;;
		*) echo "Error: Unrecognized option $1" >&2
		   usage
			;;
	esac
done

if [[ 0 -eq $flag ]]
then
	usage
fi

if [[ -d "${JUNK_FOLDER}" ]]
then
	echo "JUNK FOLDER FOUND"
else
	mkdir "${JUNK_FOLDER}"
	# TODO $JUNK_FOLDER is not a folder but exists, this will create an error
fi

echo $flag
