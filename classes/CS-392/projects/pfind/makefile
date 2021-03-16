pfind: main.o slice.o perm.o perm.h slice.h
	clang -Wall -g -o main main.o slice.o perm.o
main.o: main.c
	clang -Wall -g -c main.c
slice.o: slice.c
	clang -Wall -g -c slice.c
perm.o: perm.c
	clang -Wall -g -c perm.c
clean:
	rm -f main.o main slice.o
