#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main() {
	FILE *fp = popen("pd", "r");
	if (fp == NULL) {
		fprintf(stderr, "Error: popen() failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	char path[PATH_MAX];
	size_t count = fread(path, sizeof(char), PATH_MAX -1, fp);
	if (count == 0) {
		fprintf(stderr, "Error: fread() failed.\n");
		exit(EXIT_FAILURE);
	}
	char *eoln = strchr(path, '\n');
	if (eoln != NULL) {
		*eoln = '\n';
	} else {
		path[strlen(path)] = '\0';
	}
	printf("You are in %s\n", path);
	int status = pclose(fp);
	if (status == -1) {
		fprintf(stderr, "Error: pclose() failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	/* Use macros described under wait() to inspect 'status' in order
	   to determine success/failure of command executed by popen() */
	return !(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS);
}
