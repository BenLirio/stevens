CC     = gcc
CFLAGS = -g -Wall -Werror -pedantic-errors

all: main
main: main.c libadd.a
	$(CC) $(CFLAGS) main.c -o main libadd.a
libadd.a: add.o
	ar rs libadd.a add.o
add.o: add.c add.h
	$(CC) $(CFLAGS) -c add.c
clean:
	rm -f *.o *.a main main.exe
