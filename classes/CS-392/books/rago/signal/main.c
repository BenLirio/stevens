#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void err_sys(const char* x) {
	perror(x);
	exit(1);
}

static void sig_int(int);

int main() {
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");
	int c;
	while((c = getchar()) != EOF) {
		putchar(c);
	}
	return 0;
}

void sig_int(int signo) {
	printf("interrupt\n");
}
