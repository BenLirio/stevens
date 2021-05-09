# Ben Lirio
# I pledge my honor that I have abided by the Stevens Honor System.
mtsieve: mtsieve.o util.o sieve_thread.o
	gcc -Wall -lm mtsieve.o util.o sieve_thread.o -o mtsieve -pthread
mtsieve.o: mtsieve.c util.h sieve_thread.h
	gcc -Wall -lm -c mtsieve.c
util.o: util.c util.h
	gcc -Wall -lm -c util.c
sieve_thread.o: sieve_thread.c sieve_thread.h util.h
	gcc -Wall -lm -c sieve_thread.c
clean:
	rm -f mtsieve mtsieve.o sieve_thread.o util.o
