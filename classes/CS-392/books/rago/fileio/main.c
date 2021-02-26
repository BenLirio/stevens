#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LINE 1024

int main() {
	int fd;
	char b[MAX_LINE];
	int n;
	fd = open("./data", O_RDONLY);
	printf("%d\n", fd);
	while ((n = read(fd, b, MAX_LINE)) != 0) {
		printf("%s\n", b);
	}
	exit(0);
}
