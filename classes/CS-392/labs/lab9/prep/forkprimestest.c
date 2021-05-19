#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>


bool is_prime(unsigned long n) {
	for (int div = 2; div <= n-1; div++) {
		if (n % div == 0) {
			return false;
		}
	}
	return true;
}

void on_sig

int main() {
	int sleep_secs = 1;
	pid_t pid;
	if ((pid = fork()) == 0) {
		// Child process finds and siplays primes forever.
		unsigned long num = 2;
		unsigned int primes_count = 0;
		while (true) {
			if (is_prime(num)) {
				primes_count++;
				printf("Prime %u is %lu.\n", primes_count, num);
			}
			num++;
		}
	}

	// Sleep for the specified time and then kill the child process.
	sleep(sleep_secs);
	kill(pid, SIGINT);
	return EXIT_SUCCESS;
}
