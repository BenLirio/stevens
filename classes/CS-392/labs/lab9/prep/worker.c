#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t sig_num = 0;

void on_sig(int num) {
	sig_num = num;
}
int main() {
	struct sigaction action;
	action.sa_handler = on_sig;
	sigaction(SIGINT, &action, NULL);
	while (true) {
		printf("Working\n");
		sleep(1);
	}
}
