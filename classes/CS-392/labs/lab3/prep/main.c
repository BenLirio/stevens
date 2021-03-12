#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char filename[] = "data";
	struct stat statbuf;
	if (stat(filename, &statbuf) == -1) {
		return EXIT_FAILURE;
	}
//	printf("st_dev: %lu\n", statbuf.st_dev);
//	printf("st_ino: %lu\n", statbuf.st_ino);
//	printf("st_mode: %d\n", statbuf.st_mode);
//	printf("st_nlink: %lu\n", statbuf.st_nlink);
//	printf("st_uid: %d\n", statbuf.st_uid);
//	printf("st_gid: %d\n", statbuf.st_gid);
//	printf("st_rdev: %lu\n", statbuf.st_rdev);
	//printf("st_size: %lu\n", statbuf.st_size);
//	printf("st_blksize: %lu\n", statbuf.st_blksize);
//	printf("st_blocks: %lu\n", statbuf.st_blocks);
	int fd;
	if ((fd = open(filename, O_RDWR|O_TRUNC)) == -1) {
		fprintf(stderr, "Error: Cannot open '%s'. %s\n", filename, strerror(errno));
	}
	int n;
	off_t off;
	if ((n = write(fd, "asdf", 5)) != 5) {
		fprintf(stderr, "Error: Failed to write to file. %s\n", strerror(errno));
	}
	off = lseek(fd, 3, 0);
	if ((n = write(fd, "asdf", 5)) != 5) {
		fprintf(stderr, "Error: Failed to write to file. %s\n", strerror(errno));
	}
	if (stat(filename, &statbuf) == -1) {
		return EXIT_FAILURE;
	}
	
	printf("st_size: %lu\n", statbuf.st_size);
	printf("st_blksize: %lu\n", statbuf.st_blksize);
	printf("st_blocks: %lu\n", statbuf.st_blocks);
	if ((fd = close(fd)) == -1) {
		fprintf(stderr, "Error: Couldn't close '%s'. %s\n", filename, strerror(errno));
	}
}


