#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_FORKS 3

int parent(int pids[]) {
	int status;
	for (int i = 0; i < NUM_FORKS; i++) {
		waitpid(pids[i], &status, 0);
		printf("Child %d is done\n", pids[i]);
	}
	printf("Children done\n");
	return 0;
}

int child(int sec) {
	sleep(sec);
	printf("Child: %d\n", getpid());
	return 0;
}

int main() {
	pid_t pid;
	int pids[NUM_FORKS];
	for (int i = 0; i < NUM_FORKS; i++) {
		pid = fork();
		if (pid < 0) {
			printf("Error forking\n");
			return 1;
		}
		if (pid == 0) {
			return child(i);
		}
		pids[i] = pid;
	}
	return parent(pids);
}
