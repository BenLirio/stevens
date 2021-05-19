#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFLEN 128
#define MAX 10

int random_int_in_range(int low, int high, unsigned int *seed) {
	return low + (rand_r(seed) % (high-low+1));
}

char buffer[BUFLEN];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t producer_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t consumer_cond = PTHREAD_COND_INITIALIZER;
bool expression_ready = false;

void* consume(void *ptr) {
	int num_consumed = 0;
	while (num_consumed++ < MAX) {
		pthread_mutex_lock(&mutex);

		while (!expression_ready) {
			pthread_cond_wait(&consumer_cond, &mutex);
		}
		int a, b;
		sscanf(buffer, "%d + %d", &a, &b);
		printf("Consumer[%d]: %d + %d = %d\n", num_consumed, a, b, a+b);
		expression_ready = false;
		pthread_cond_signal(&producer_cond);

		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* produce(void *ptr) {
	unsigned int seed = 1;
	for (int i = 0; i < MAX; i++) {
		int a = random_int_in_range(0, 9, &seed);
		int b = random_int_in_range(0, 9, &seed);
		pthread_mutex_lock(&mutex);

		while (expression_ready) {
			pthread_cond_wait(&producer_cond, &mutex);
		}
		sprintf(buffer, "%d + %d", a, b);
		expression_ready = true;

		pthread_cond_signal(&consumer_cond);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main() {
	pthread_t consumer_thread;
	pthread_t producer_thread;

	// Create Threads
	pthread_create(&consumer_thread, NULL, consume, NULL);
	pthread_create(&producer_thread, NULL, produce, NULL);

	// Join Threads
	pthread_join(consumer_thread, NULL);
	pthread_join(producer_thread, NULL);
}

