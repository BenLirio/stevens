#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <process name>\n", argv[0]);
		return EXIT_FAILURE;
	}
	int ps_to_grep[2];
	int grep_to_parent[2];
	if (pipe(ps_to_grep) < 0) {
		fprintf(stderr, "Error: Cannot create pipe ps_to_grep. %s\n",strerror(errno));
		return EXIT_FAILURE;
	}
	if (pipe(grep_to_parent) < 0) {
		fprintf(stderr, "Error: Cannot create pipe grep_to_parent. %s\n",strerror(errno));
		return EXIT_FAILURE;
	}

	pid_t pid[2];
	if (pid[0] == fork()) {
		// PS
		close(ps_to_grep[0]);
		dup2(ps_to_grep[1], STDOUT_FILENO);
		close(grep_to_parent[0]);
		close(grep_to_parent[1]);

		execlp("ps", "ps", "-aux", NULL);
		return 0;
	}
	if (pid[0] == fork()) {
		close(ps_to_grep[1]);
		dup2(ps_to_grep[0], STDIN_FILENO);
		close(grep_to_parent[0]);
		dup2(grep_to_parent[1], STDOUT_FILENO);
		execlp("grep", "grep", argv[1],NULL);
		return 0;
	}
	close(ps_to_grep[0]);
	close(ps_to_grep[1]);
	close(grep_to_parent[1]);
	dup2(grep_to_parent[0], STDIN_FILENO);
	char buffer[4096];
	ssize_t n;
	while (1) {
		n = read(STDIN_FILENO, buffer, sizeof(buffer));
		if (n == -1) {
			if (errno == EINTR) {
				continue;
			} else {
				perror("read()");
				exit(EXIT_FAILURE);
			}
		}
		if (n == 0) {
			break;
		}
		write(STDOUT_FILENO, buffer, n);
	}
	wait(NULL);
	wait(NULL);
}
