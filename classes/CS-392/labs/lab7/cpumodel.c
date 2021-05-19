/*
Ben Lirio
I pledge my honor that I have abided by the Stevens Honor System.
*/
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 256

bool starts_with(const char *str, const char *prefix) {
    /* TODO:
       Return true if the string starts with prefix, false otherwise.
       Note that prefix might be longer than the string itself.
     */
	if (*prefix != *str)
		return false;
	while (*(++prefix) == *(++str))
		;
	if (*prefix == '\0')
		return true;
	return false;
}

int main() {
	int status;
	FILE* cpuinfo_pipe;
    /* TODO:
       Open "cat /proc/cpuinfo" for reading, redirecting errors to /dev/null.
       If it fails, print the string "Error: popen() failed. %s.\n", where
       %s is strerror(errno) and return EXIT_FAILURE.
     */
	cpuinfo_pipe = popen("cat /proc/cpuinfo 2>/dev/null", "r");
	if (cpuinfo_pipe == NULL) {
		fprintf(stderr, "Error: popen() failed. %s\n", strerror(errno));
		return EXIT_FAILURE;
	}


    /* TODO:
       Allocate an array of 256 characters on the stack.
       Use fgets to read line by line.
       If the line begins with "model name", print everything that comes after
       ": ".
       For example, with the line:
       model name      : AMD Ryzen 9 3900X 12-Core Processor
       print
       AMD Ryzen 9 3900X 12-Core Processor
       including the new line character.
       After you've printed it once, break the loop.
     */
	 char buf[BUF_SIZE];
	 char prefix[] = "model name";
	 while(fgets(buf, BUF_SIZE, cpuinfo_pipe) != NULL) {
		if (!starts_with(buf, prefix)) {
			continue;
		}
		char *p = buf;
		while(*(p++) != ':')
			;
		p++;
		printf("%s", p);
		break;
	 }


    /* TODO:
       Close the file descriptor and check the status.
       If closing the descriptor fails, print the string
       "Error: pclose() failed. %s.\n", where %s is strerror(errno) and return
       EXIT_FAILURE.
     */
	status = pclose(cpuinfo_pipe);
	if (status == -1) {
		fprintf(stderr, "Error: pclose() failed. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}
    return !(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS);
}
