CC		= gcc
CFLAGS	= -g -Wall -Werror -pedantic

all: chatclient chatserver
chatclient: chatclient.o
	$(CC) $(CFLAGS) $< -o $@
chatserver: chatserver.o
	$(CC) $(CFLAGS) $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f chatclient chatserver *.o
