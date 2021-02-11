#!/bin/bash

if [ "$#" -eq 0 ]
then

# ---- begin here document ---- #
cat << EOF
Usage: junk.sh [-hlp] [list of files]
	-h: Display help
	-l: List junked files.
	-p: Purge all files.
	[list of files] with no other arguments to junk those files.
EOF
# ---- end here document ---- #

fi
