#Name        : sort.c
#Author      : Ben Lirio
#Date        : 3/2/21
#Description : Uses quicksort to sort a file of either ints, doubles, or
#              strings.
#Pledge      : I pledge my honor that I have abided by the Stevens Honor System.

sort: sort.o quicksort.o
	gcc -o sort sort.o quicksort.o

sort.o: sort.c
	gcc -c sort.c
quicksort.o: quicksort.c
	gcc -c quicksort.c
clean:
	rm sort sort.o quicksort.o
