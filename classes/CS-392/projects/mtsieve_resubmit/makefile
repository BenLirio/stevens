# Ben Lirio
# I pledge my honor that I have abided by the Stevens Honor System.
CC	= gcc
CFLAGS	= -g -Wall -Werror -pedantic
LDFLAGS = -lm -pthread


mtsieve: mtsieve.o util.o sieve_thread.o
	$(CC) $(CFLAGS) -o $@ mtsieve.o util.o sieve_thread.o $(LDFLAGS)
mtsieve.o: mtsieve.c util.h sieve_thread.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)
util.o: util.c util.h
	$(CC) $(CLFAGS) -c $< $(LDFLAGS)
sieve_thread.o: sieve_thread.c sieve_thread.h util.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)
clean:
	rm -f mtsieve *.o
