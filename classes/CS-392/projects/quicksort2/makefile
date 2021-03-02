sort: sort.o quicksort.o
	clang -g -o sort sort.o quicksort.o

sort.o: sort.c
	clang -g -c sort.c
quicksort.o: quicksort.c
	clang -g -c -gline-tables-only quicksort.c
