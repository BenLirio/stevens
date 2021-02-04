#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 4098

int main() {
	char	buf[MAXLINE];
	pid_t	pid;
	int	status;
	void*	err;
	printf("%% ");
	while (1) {
		err = fgets(buf, MAXLINE, stdin);
		if (err == NULL)
			break;
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		if ((pid = fork()) < 0)
			return 1;
		else if (pid == 0) {
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}
		if ((pid == waitpid(pid, &status, 0)) < 0)
			return 1;
		printf("%% ");
	}
	exit(0);
}
