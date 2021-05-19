#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define BUFLEN 1000
#define MAX_EXPRS 2
#define QUEUE_LEN 1
#define MAX_STRLEN 16

int rand_int_in_range(int low, int high, unsigned int* seed) {
	return low + (rand_r(seed) % (high-low+1));
}

char *queue[QUEUE_LEN];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t producer_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t consumer_cond = PTHREAD_COND_INITIALIZER;
int num_occupied = 0;
int read_index = 0;
int write_index = 0;
int num_consumed = 0;
int num_produced = 0;

void* produce(void* ptr) {
	int id = *(int*)ptr;
	unsigned int seed = time(NULL)^id;
	while(true) {
		pthread_mutex_lock(&mutex);
		if (num_produced >= MAX_EXPRS) {
			pthread_mutex_unlock(&mutex);
			break;
		}

		while (num_occupied >= QUEUE_LEN) {
			pthread_cond_wait(&producer_cond, &mutex);
		}
		int a = rand_int_in_range(0, 9, &seed);
		int b = rand_int_in_range(0, 9, &seed);
		sprintf(queue[write_index], "%d + %d", a, b);
		printf("Producer[%d]: %d + %d\n", id, a, b);
		write_index = (write_index + 1)%QUEUE_LEN;
		num_produced++;
		num_occupied++;
		pthread_cond_signal(&consumer_cond);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
void* consume(void* ptr) {
	int id = *(int*)ptr;
	while(true) {
		pthread_mutex_lock(&mutex);
		if (num_consumed >= MAX_EXPRS) {
			pthread_mutex_unlock(&mutex);
			break;
		}
		
		while(num_occupied <= 0) {
			pthread_cond_wait(&consumer_cond, &mutex);
		}

		int a;
		int b;
		sscanf(queue[read_index], "%d + %d", &a, &b);
		printf("Consumer[%d]: %d + %d = %d\n", id, a, b, a+b);
		read_index = (read_index + 1) % QUEUE_LEN;
		num_consumed++;
		num_occupied--;
		pthread_cond_signal(&producer_cond);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main() {
	pthread_t producer_threads[NUM_PRODUCERS];
	pthread_t consumer_threads[NUM_CONSUMERS];
	int consumer_thread_ids[NUM_CONSUMERS];
	int producer_thread_ids[NUM_PRODUCERS];
	for (int i = 0; i < NUM_CONSUMERS; i++) {
		consumer_thread_ids[i] = i;
	}
	for (int i = 0; i < NUM_PRODUCERS; i++) {
		producer_thread_ids[i] = i;
	}

	for (int i = 0; i < QUEUE_LEN; i++) {
		queue[i] = (char*)malloc(sizeof(char)*MAX_STRLEN);
	}

	// Create threads
	for (int i = 0; i < NUM_PRODUCERS; i++) {
		int id = i;
		pthread_create(&producer_threads[i], NULL, produce, &producer_thread_ids[i]);
	}
	for (int i = 0; i < NUM_CONSUMERS; i++) {
		int id = i;
		pthread_create(&consumer_threads[i], NULL, consume, &consumer_thread_ids[i]);
	}




	// Join threads
	for (int i = 0; i < NUM_PRODUCERS; i++) {
		pthread_join(producer_threads[i], NULL);
	}
	for (int i = 0; i < NUM_CONSUMERS; i++) {
		pthread_join(consumer_threads[i], NULL);
	}
	printf("Num Produced: %d\n", num_produced);
	printf("Num Consumed: %d\n", num_consumed);
	for (int i = 0; i < QUEUE_LEN; i++) {
		free(queue[i]);
	}
}
