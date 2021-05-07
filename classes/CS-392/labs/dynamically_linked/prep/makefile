CC		= gcc
CFLAGS	= -g -Wall -Werror -pedantic-errors

default: my_dl2.so my_dl.so dl_practice

dl_practice: dl_practice.o
	$(CC) $(CFLAGS) -o $@ $^ -ldl
dl_practice.o: dl_practice.c
	$(CC) $(CFLAGS) -c dl_practice.c

my_dl.so: my_dl.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^
my_dl2.so: my_dl2.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

clean:
	rm -f my_dl.so dl_practice *.o
