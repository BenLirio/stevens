#include <stdio.h>
#include <limits.h>

// Make sure ARG_MAX is defined and set to the right value
#ifndef _POSIX_ARG_MAX
#define _POSIX_ARG_MAX 4096
#endif
#ifndef ARG_MAX
#define ARG_MAX _POSIX_ARG_MAX
#endif


int main() {
	char* cmd_argv[ARG_MAX];
	printf("%d\n", ARG_MAX);
}
