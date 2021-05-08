#BEN LIRIO
#I pledge my honor that I have abided by the Stevens Honor System.
CC		= gcc
CFLAGS	= -g -Wall -Werror -pedantic

all: chatclient
chatclient: chatclient.o
	$(CC) $(CFLAGS) $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f chatclient chatserver *.o
