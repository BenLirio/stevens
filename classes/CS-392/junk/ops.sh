#!/bin/bash

E_OPTERR=65

if [ "$#" -eq 0 ]
then
	echo "Usage $0 -[options a,b,c]"
	exit $E_OPTERR
fi
