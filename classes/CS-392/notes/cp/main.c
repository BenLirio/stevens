#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 128

/**
	This program trivially copies a file from one location to another.
*/
void display_usage(char *progname) {
	printf("Usage: %s <source> <destination>\n", progname);
}

int main(int argc, char*argv[]) {
	if (argc != 3) {
		display_usage(argv[0]);
		return EXIT_FAILURE;
	}
	struct stat src_sb;
	stat(argv[1], &src_sb);

	if ((open
}
/*
int main(int argc, char*argv[]) {
	int src_fd, dst_fd;
	if (argc != 3) {
		display_usage(argv[0]);
		return EXIT_FAILURE;
	}
	struct stat src_sb;
	int retval = (stat(argv[1], &src_sb));
	if ((src_fd = open(argv[1], O_RDONLY)) == -1) {
		fprintf(stderr, "Error: Cannot open source file '%s'. %s.\n",
		argv[1], strerror(errno));
	}
	struct stat dst_sb;
	if (stat(argv[1], &dst_sb) < 0) {
		fprintf(stderr, "Error: Cannot stat source file '%s'. %s\n",
			argv[1], strerror(errno));
			close(src_fd);
			return EXIT_FAILURE;
	}
	if ((dst_fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, dst_sb.st_mode)) == -1) {
		fprintf(stderr, "Error: Cannot open source file '%s'. %s.\n",
		argv[2], strerror(errno));
	}
	char *buf;
	if ((buf = (char*)malloc(sizeof(char) * BUFSIZE)) == NULL) {
		fprintf(stderr, "Error: malloc failed.\n");
		close(src_fd);
		close(dst_fd);
		return EXIT_FAILURE;
	}
	int bytes_read;
	while ((bytes_read = read(src_fd, buf, BUFSIZE)) > 0) {
		if (write(dst_fd, buf, bytes_read) != bytes_read) {
			fprintf(stderr, "Error: failed to write to file '%s'. %s.\n",
				argv[2], strerror(errno));
			free(buf);
			close(src_fd);
			close(dst_fd);
			return EXIT_FAILURE;
		}
	}
	if (bytes_read == -1) {
		fprintf(stderr, "Error: Failed to read fom file '%s'. %s.\n",
			argv[1], strerror(errno));
		free(buf);
		close(src_fd);
		close(dst_fd);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}*/
