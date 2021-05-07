CC		= gcc
CFLAGS	= -g -Wall -Werror -pedantic

all: chatclient chatserver
chatclient: chatclient.o
	$(CC) $(CFLAGS) $< -o $@
chatclient.o: chatclient.c
	$(CC) $(CFLAGS) -c $<

chatserver: chatserver.o
	$(CC) $(CFLAGS) $< -o $@
chatserver.o: chatserver.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f chatclient chatserver *.o
