############################################################
# Author: Ben Lirio
# Date: 2/16/21
# Pledge: I plege my honor that I have abided by the Stevens Honor System
# Description: Junk project. An alternative to rm. Moves the file to a folder instead of removing it.
############################################################
#!/bin/bash

readonly STREAM_TO_NULL=/dev/null
readonly FALSE=0
readonly TRUE=1
readonly let HELP_FLAG=$(( 2#0001 ))
readonly let LIST_FLAG=$(( 2#0010))
readonly let PURGE_FLAG=$(( 2#0100 ))
readonly let INCORRECT_FLAG=$(( 2#1000 ))
readonly JUNK_FOLDER=~/.junk

usage ()
{
	cat << EOF
Usage: $(basename $0) [-hlp] [list of files]
	-h: Display help
	-l: List junked files.
	-p: Purge all files.
	[list of files] with no other arguments to junk those files.
EOF
}

incorrect_option=""

parse_flags ()
{
	local flag=$(( 2#0 ))

	while getopts ":h :l :p" opt; do
		case ${opt} in
			h) flag=$(( flag | HELP_FLAG ))
				;;
			l) flag=$(( flag | LIST_FLAG ))
				;;
			p) flag=$(( flag | PURGE_FLAG ))
				;;
			*) incorrect_option="${1}"
			   flag=$(( flag | INCORRECT_FLAG ))
				;;
		esac
	done
	return $flag
}

setup_junk_folder ()
{
	if [[ ! -e "${JUNK_FOLDER}" ]]
	then
		mkdir ${JUNK_FOLDER}
	fi
	if [[ ! -d "${JUNK_FOLDER}" ]]
	then
		echo "${JUNK_FOLDER} exists, but is not a directory"
		exit 1
	fi
}

junk_files ()
{
	for filename in $*
	do
		if [[ -e $filename ]]
		then
			mv ${filename} ${JUNK_FOLDER}
		else
			echo "Warning: '${filename}' not found"
		fi
	done
}

list_junk ()
{
	ls -lAF "${JUNK_FOLDER}"

}

purge_junk ()
{
	rm -rf "${JUNK_FOLDER}"/* 
	# Not the best practice but it functions properly
	rm -rf "${JUNK_FOLDER}"/.* 2>${STREAM_TO_NULL}
}

log_incorrect_option ()
{
	echo "Error: Incorrect option '${incorrect_option}'"
	usage
	exit 1
}

too_many_options ()
{
	echo "Error: Too many options enabled."
	usage
	exit 1
}

parse_flags $*; flag=$?

shift $(( OPTIND - 1))
[[ $# -eq 0 ]] && has_args=$FALSE || has_args=$TRUE
[[ $flag -eq 0 ]] && has_flags=$FALS || has_flags=$TRUE

if [[ has_args -eq has_flags ]]
then
	if [[ has_args -eq $FALSE ]]
	then
		usage
		exit 1
	else
		too_many_options
	fi
fi

setup_junk_folder

case "${flag}" in
	0) junk_files $*
		;;
	1) usage
		;;
	2) list_junk
		;;
	4) purge_junk
		;;
	8) log_incorrect_option
		;;
	*) too_many_options
		;;
esac

exit 0
