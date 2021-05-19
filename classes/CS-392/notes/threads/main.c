#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num_running = 0;
pthread_mutex_t lock;

void *sleep_print(void *ptr) {
	printf("Thread %d is running.\n", *(int*)ptr);
	num_running--;
	pthread_exit(NULL);
}

int main() {
	int num_threads = 5000;
	pthread_t *threads;
	if ((threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t))) == NULL) {
		fprintf(stderr, "error: Cannot allocate memory for threads. \n");
		return EXIT_FAILURE;
	}

	int *thread_nums;
	if ((thread_nums = (int *)malloc(num_threads * sizeof(int))) == NULL) {
		free(threads);
		fprintf(stderr, "Error: Cannot allocate memory for thread args.\n");
		return EXIT_FAILURE;
	}
	pthread_mutex_init(&lock, NULL);
	// Create independent threads.
	int num_started = 0;
	for (int i = 0; i < num_threads; i++) {
		thread_nums[i] = i+1;
		int retval;
		if ((retval = pthread_create(threads+i, NULL, sleep_print, (void*)(&thread_nums[i]))) != 0) {
			fprintf(stderr, "Error: cannot create thread %d. "
					"No more threads will be created. %s.\n",
					i+1, strerror(retval));
		}
		num_started++;
		num_running++;
	}
	// Wait until threads are complete until main continues.
	// If we don't wait we run the risk of executing an exit, which will terminate the process
	// and all threads before the threads have completed.
	for (int i = 0; i < num_started; i++) {
		if (pthread_join(threads[i], NULL) == -1) {
			fprintf(stderr, "Warning: Thread %d did not join properly.\n");
		}
	}

	// We did not join the threads in this example, so you might not get
	// to see all threas having executed.

	printf("Num threads started: %d\nThreads still running: %d\n", num_started, num_running);

}
