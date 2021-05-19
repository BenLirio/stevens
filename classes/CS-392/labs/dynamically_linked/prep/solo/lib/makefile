CC		= gcc
CFLAGS 	= -g
default: my_add.so

my_add.so: my_add.c
	$(CC) -shared -fPIC -o $@ $^
