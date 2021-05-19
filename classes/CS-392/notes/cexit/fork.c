#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid;
	int w = 100;
	if ((pid = fork()) < 0) {
		perror("for");
		return -1;
	}
	if (pid == 0) {
		printf("Child\n");
		return 0;
	} else {
		printf("Parent\n");
		return 0;
	}
}
