#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void sigusr1_handler(int sig) {
	printf("killing\n");
}

int main() {
	struct sigaction sa;	

	memset(&sa, 0, sizeof(struct sigaction));

	sa.sa_handler = sigusr1_handler;
	sigemptyset(&sa.sa_mask);
	/* If a blocking system call was interrupted (think "read()"), the system
	 * call is restarted. If it fails to restart, then the system call fails
	 * and errno is set to EINT. */
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGUSR1, &sa, NULL) < 0) {
		fprintf(stderr, "Error: Could not register signal handler. %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	int t = 0;
	while (true) {
		sleep(1);
		t++;
	}
}
