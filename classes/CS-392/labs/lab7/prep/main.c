#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <process name>\n", argv[0]);
		return EXIT_FAILURE;
	}
	int ps_to_grep[2], grep_to_wc[2], wc_to_parent[2];
	pipe(ps_to_grep);
	pipe(grep_to_wc);
	pipe(wc_to_parent);

	pid_t pid[3];
	if ((pid[0] = fork()) == 0) {
		// ps
		close(ps_to_grep[STDIN_FILENO]);
		dup2(ps_to_grep[STDOUT_FILENO], STDOUT_FILENO);
		close(grep_to_wc[STDIN_FILENO]);
		close(grep_to_wc[STDOUT_FILENO]);
		close(wc_to_parent[STDIN_FILENO]);
		close(wc_to_parent[STDOUT_FILENO]);

		write(STDOUT_FILENO, "abc", 4);
		return EXIT_SUCCESS;
	}
	if ((pid[1] = fork()) == 0) {
		// grep
		dup2(ps_to_grep[STDIN_FILENO], STDIN_FILENO);
		close(ps_to_grep[STDOUT_FILENO]);
		close(grep_to_wc[STDIN_FILENO]);
		dup2(grep_to_wc[STDOUT_FILENO], STDOUT_FILENO);
		close(wc_to_parent[STDIN_FILENO]);
		close(wc_to_parent[STDOUT_FILENO]);
		char b[4];
		int n = read(STDIN_FILENO, b, 4);
		write(STDOUT_FILENO, b, n);
		return EXIT_SUCCESS;
	}
	if ((pid[1] = fork()) == 0) {
		// wc
		close(ps_to_grep[STDIN_FILENO]);
		close(ps_to_grep[STDOUT_FILENO]);
		dup2(grep_to_wc[STDIN_FILENO], STDIN_FILENO);
		close(grep_to_wc[STDOUT_FILENO]);
		dup2(wc_to_parent[STDOUT_FILENO], STDOUT_FILENO);
		close(wc_to_parent[STDOUT_FILENO]);
		printf("asdf\n");
		char b[4];
		int n = read(STDIN_FILENO, b, 4);
		write(STDOUT_FILENO, b, n);
		return EXIT_SUCCESS;
	}
	char b[4];
	int n = read(wc_to_parent[STDIN_FILENO], b, 4);
	write(STDOUT_FILENO, b, n);
	wait(NULL);
	wait(NULL);
	wait(NULL);
}
