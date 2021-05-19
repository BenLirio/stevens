#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		//execlp("ls", "ls","-aaa", "hello world", (char*)NULL);
		printf("Child\n");
		return 0;
	} else {
		printf("Parent\n");
	}
	int status;
	wait(&status);
	printf("status: %d\n", status);
}
