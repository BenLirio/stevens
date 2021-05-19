#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include <stdio.h>
#include "semaphore.h"

#define SCALE_FACTOR 1000000

int random_int_in_range(int low, int high) {
	return rand()%(high-low+1);
}

void random_sleep() {
	srand(time(NULL)^getpid());
	useconds_t sleep_time = (useconds_t)random_int_in_range(0*SCALE_FACTOR, 0.75*SCALE_FACTOR);
	usleep(sleep_time);
}

int main() {
	int key;
	int retval = EXIT_SUCCESS;
	int shmid;
	int sem;
	char *shbuf = (char*)-1;

	// This creates the context to create the semephore in
	if ((key = ftok("./", 'c')) == -1) {
		fprintf(stderr, "Error: Failed to generate key. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	// This is a token used to create a chunk of memory
	if ((shmid = shmget(key, sizeof(char)*1024, IPC_CREAT | 0666)) == -1) {
		fprintf(stderr, "Error: Failed to get semid. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	// attach to the memory
	if ((shbuf = (char*)shmat(shmid, NULL, 0)) == (char*)-1) {
		fprintf(stderr, "Error: Failed to attach shared memory. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	if (sem = create_semaphore(key) == -1) {
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	if (set_sem_value(sem, 1) == EXIT_FAILURE) {
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	if (fork() == 0) {
		random_sleep();
		if (P(sem) == -1) {
			return EXIT_FAILURE;
		}
		if (V(sem) == -1) {
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	if (fork() == 0) {
		random_sleep();
		return EXIT_SUCCESS;
	}
	wait(NULL);
	wait(NULL);

	EXIT:
	/*
	if (sem != -1 && del_sem_value(sem) == EXIT_FAILURE) {
		printf("Failed to delete semaphore\n");
		retval = EXIT_FAILURE;
	}
	if (shbuf != (char*) -1 && shmdt((void*)shbuf) == -1) {
		fprintf(stderr, "Error: Failed to detach shared memory. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
	}
	if (shmid != -1 && shmctl(shmid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "Error: Failed to delete shared memory. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
	}
	*/
	return retval;
}
