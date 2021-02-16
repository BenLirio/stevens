#include <termio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	struct termios 	term;
	long		vdisable;

	if (isatty(STDIN_FILENO) == 0) {
		printf("Standard input is not a terminal device\n");
		exit(1);
	}

	if ((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)) < 0) {
		printf("fpathconf error or _POSIX_VDISABLE not in effect\n");
		exit(1);
	}

	if (tcgetattr(STDIN_FILENO, &term) < 0) { /* Fetch tty state */
		printf("tcgetattr error\n");
		exit(1);
	}
	term.c_cc[VINTR] = vdisable; /* disable INTR character */
	term.c_cc[VEOF] = 2;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0) {
		printf("tcsetattr error");
		exit(1);
	}
	exit(0);
}
