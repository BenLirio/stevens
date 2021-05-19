#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void* primes_thread(void* arg) {
	struct timespec rqtp;
	rqtp.tv_sec = 1;
	rqtp.tv_nsec = 0;
	struct timespec* rmtp = malloc(sizeof(struct timespec));
	printf("Going to sleep for %lds %ldns\n", rqtp.tv_sec, rqtp.tv_nsec);
	nanosleep(&rqtp, rmtp);
	printf("Slept for %lds %ldns\n", rmtp->tv_sec, rmtp->tv_nsec);
	free(rmtp);
	return NULL;
}

int main() {
	pthread_t p1;
	int retval = 0;
	if ((retval = pthread_create(&p1, NULL, primes_thread, NULL)) != 0) {
		fprintf(stderr, "Error: pthread_create failed. %s.\n", strerror(retval));
		return EXIT_FAILURE;
	}
	if ((retval = pthread_join(p1, NULL)) != 0) {
		fprintf(stderr, "Error: pthread_join failed. %s.\n", strerror(retval));
		return EXIT_FAILURE;
	}
}
