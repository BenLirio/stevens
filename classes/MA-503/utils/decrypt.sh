#!/bin/bash

for i in {1..1373}
do
	K=$(./main 805 ${i} 1373)
	if [[ K -eq 397 ]]
	then
		echo $i
	fi
done
