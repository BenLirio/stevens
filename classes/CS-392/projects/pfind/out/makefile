#/*******************************************************************************
#* Name        : makefile
# * Author      : Ben Lirio
# * Date        : 03/16/21
# * Description : Make file
# * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
# ******************************************************************************/
pfind: pfind.o slice.o perm.o perm.h slice.h
	gcc -Wall -g -o pfind pfind.o slice.o perm.o
pfind.o: pfind.c
	clang -Wall -g -c pfind.c
slice.o: slice.c
	clang -Wall -g -c slice.c
perm.o: perm.c
	clang -Wall -g -c perm.c
clean:
	rm -f pfind pfind.o slice.o perm.o
