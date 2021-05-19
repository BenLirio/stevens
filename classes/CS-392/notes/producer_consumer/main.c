#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX 10
#define BUFLEN 128
#define SCALE_FACTOR 1000000

char buffer[BUFLEN];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t producer_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t consumer_cond = PTHREAD_COND_INITIALIZER;
bool expression_ready = false;

int random_int_in_range(int, int, unsigned int*);
void* produce(void*);
void* consume(void*);

int main() {
	pthread_t threads[2];

	// Create one producer and one consumer thread.
	int retval;
	if ((retval = pthread_create(&threads[0], NULL, produce, NULL)) != 0) {
		fprintf(stderr, "Error: Cannot create producer thread. %s.\n", strerror(retval));
		return EXIT_FAILURE;
	}
	if ((retval = pthread_create(&threads[1], NULL, consume, NULL)) != 0) {
		fprintf(stderr, "Error: Cannot create consumer thread. %s.\n", strerror(retval));
		return EXIT_FAILURE;
	}

	// Wait for all thread to finnish
	for (int i = 0; i < 2; i++) {
		pthread_join(threads[i], NULL);
	}

	return EXIT_SUCCESS;
}

int random_int_in_range(int low, int high, unsigned int *seed) {
	int val = low + rand_r(seed)%(high-low+1);
	return val;
}

void* produce(void* arg) {
	unsigned int seed = (unsigned int)((time(NULL)&0xFFFF))|((long)pthread_self() << 16);
	int num_produced = 0;
	while (num_produced++ < MAX) {
		pthread_mutex_lock(&mutex);

		while (expression_ready) {
			pthread_cond_wait(&producer_cond, &mutex);
		}
		int a = random_int_in_range(0, 9, &seed);
		int b = random_int_in_range(0, 9, &seed);
		sprintf(buffer, "%d + %d", a, b);
		printf("Producer: %s\n", buffer);
		expression_ready = true;

		// Notify the ocnsumer data is available
		pthread_cond_signal(&consumer_cond);
		fflush(stdout);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* consume(void* arg) {
	int num_consumed = 0;
	while (num_consumed++ < MAX) {
		// Lock the mutex
		pthread_mutex_lock(&mutex);

		// pthread_cond_wait must be place in a while loop.
		// pthread_cond_wait atomically unlocks the mutex and waits for the 
		// condition variable to be signed.
		// Unlocking the mutex and suspending on the condition variable is done
		// automatically
		while (!expression_ready) {
			pthread_cond_wait(&consumer_cond, &mutex);
		}

		int a;
		int b;
		sscanf(buffer, "%d + %d", &a, &b);
		printf("Consumer[%d]: %d + %d = %d\n", num_consumed, a, b, a+b);
		expression_ready = false;
		// Notify the producer that the data has been consumed
		pthread_cond_signal(&producer_cond);
		fflush(stdout);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
