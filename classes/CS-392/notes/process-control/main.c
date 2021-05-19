#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
	char cmd[] = "/usr/bin/echo";
	pid_t pid;

	printf("PID: %ld\n", (long)getpid());

	if ((pid = fork()) < 0) {
		fprintf(stderr, "Error: fork() failed. %s\n", strerror(errno));
		return EXIT_FAILURE;
	} if (pid > 0) {
		printf("Child PID: %ld\n", (long)pid);
		do {
			if (w == -1) {
				// waitpid failed
				perror("waitpid()");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status)) {
				printf("Child process %ld exited, status=%d.\n", (long)pid, WEXITSTATUS(status));
			}
			else if (WIFSIGNALED(status)) {
				printf("Child process %ld killed by signal %d.\n", (long)pid, WTERMSIG(status));
			} else if (WIFCONTINUED(status)) {
				printf("Child process continued.");
			}
		} while(1);
	} else {

	}

	return EXIT_SUCCESS;
}
