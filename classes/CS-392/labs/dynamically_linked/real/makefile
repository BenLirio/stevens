CC     = gcc
CFLAGS = -g -Wall -Werror -pedantic-errors

all: main libsum.so

# TODO: build main
main: main.o
	$(CC) $(CFLAGS) -o $@ $< -ldl

main.o: main.c
	$(CC) $(CFLAGS) -c $<


# TODO: build libsum.so
libsum.so: sum.c sum.h
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^


clean:
	rm -f libsum.so main main.exe
