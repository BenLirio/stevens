#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

volatile sig_atomic_t got_signal = 0;

void catch_alarm(int sig) {
	got_signal = 1;
}

/* Brute force method to test if a number is prime. */
bool is_prime(unsigned long n) {
	for (int i = 0; i < n; i++) {
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
	}
	int sleep_seconds = atoi(argv[1]);

	if (sleep_seconds <= 0) {
		fprintf(stderr, "Error: Invalid number of seconds '%s' for sleep time.\n", argv[1]);
		return EXIT_FAILURE;
	}
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = catch_alarm;
	action.sa_flags = SA_RESTART;

	if (sigaction(SIGALRM, &action, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}

	alarm(sleep_seconds);

	unsigned long last_prime = 2, num = 2;
	while (true) {
		if (got_signal) {
			printf("Prime %u is %lu.\n", primes_count, last_prime);
			break;
		}
		if (is_prime(num)) {
			primes_count++;
			last_prime = num;
		}
		num++;
	}
	return EXIT_SUCCESS;
}
