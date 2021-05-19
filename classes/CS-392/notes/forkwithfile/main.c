#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFSIZE 128
#define INFILE "main.c"

int main() {
	int fd;
	char buf[BUFSIZE];
	printf("PID: %ld\n", (long)getpid());
	printf("Each process will read in and print out op to 127 characters\n");
	fflush(stdout);

	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Error: fork() failed. %s\n", strerror(errno));
		return EXIT_FAILURE;
	} else if (pid > 0) {
		// We're in the parent.
		fd = open(INFILE, O_RDONLY);
		read(fd, &buf, BUFSIZE-1);		
		buf[BUFSIZE-1] = '\0';
		printf("\nParrent read:\n---------------------------------\n%s\n"
		"----------------------------------\n", buf);
		fflush(stdout);
		close(fd);
		
		int status;
		do {
			// Wait for the child to complete and get the status of how it
			// terminated
			pid_t w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			if (w == -1) {
				// waitpid failed.
				perror("waitpid()");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status)) {
				printf("Child process %ld exited, status=%d.\n", (long)pid,
					WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {
				printf("Child process %ld killed by signal %d\n", (long)pid,
					WTERMSIG(status));
			} else if (WIFSTOPPED(status)) {
				printf("Child process %ld stopped by signal %d.\n", (long)pid,
					WSTOPSIG(status));
			} else if (WIFCONTINUED(status)) {
				printf("Child process %ld continued.\n", (long)pid);
			}
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	} else {
		// We're in the child.
		printf("Child PID: %ld\n", (long)getpid());
		sleep(2000);
		fd = open(INFILE, O_RDONLY);
		read(fd, &buf, BUFSIZE-1);		
		buf[BUFSIZE-1] = '\0';
		printf("\nChild read:\n---------------------------------\n%s\n"
		"----------------------------------\n", buf);
		fflush(stdout);
		close(fd);

	}

}
