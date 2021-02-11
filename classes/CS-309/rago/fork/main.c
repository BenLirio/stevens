#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 2048

void err_sys(char*);
int main() {
	int c;
	int status;
	pid_t pid;

	char buff[MAXLINE];
	while (fgets(buff, MAXLINE, stdin) != NULL) {
		if (buff[strlen(buff) - 1] == '\n')
			buff[strlen(buff) - 1] = 0;
		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {
			execlp(buff, buff, (char *)0);
			printf("couln't execute: %s\n", buff);
			exit(127);
		}
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
	}
	exit(0);
}
void err_sys(char* msg) {
	printf("%s\n", msg);
	exit(1);
}
