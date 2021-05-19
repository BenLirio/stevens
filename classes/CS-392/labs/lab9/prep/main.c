#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

sig_atomic_t signal_val = 0;

void catch_signal(int sig) {
	signal_val = sig;
}

int main() {
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = catch_signal;
	action.sa_flags = SA_RESTART; /* Restart syscalls if possible */

	if (sigaction(SIGINT, &action, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}

	if (sigaction(SIGTERM, &action, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}

	while(true) {
		if (!signal_val) {
			printf("I am busy working. Do not disturb me!\n");
		} else if (signal_val == SIGINT) {
			printf("Sig int recieved\n");
			signal_val = 0;
		} else if (signal_val == SIGTERM) {
			printf("Sig term recieved\n");
			signal_val = 0;
		}
		sleep(1);
	}
	return EXIT_SUCCESS;
}
