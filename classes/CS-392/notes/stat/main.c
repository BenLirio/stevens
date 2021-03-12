#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 128

/*
Read all files within current directory
Display absolute address and last mod time
*/
int main() {
	DIR *dir;
	if ((dir = opendir(".")) == NULL) {
		fprintf(stderr, "Error: Cannot open current directory.\n");
		exit(EXIT_FAILURE);
	}

	char buf[PATH_MAX];
	char timebuf[BUFSIZE];
	struct stat sb;
	struct dirent *de;
	while ((de = readdir(dir)) != NULL) {
		char *res = realpath(de->d_name, buf);
		if (!res) {
			fprintf(stderr, "Error: realpath() failed. %s\n", strerror(errno));
		}
		if (!stat(buf, &sb)) {
			strftime(timebuf, BUFSIZE, "%b %d %Y %H:%M",
					localtime(&sb.st_mtime));
			printf("%s [%s]\n", buf, timebuf);
		} else {
			printf("%s\n", buf);
		}
	}
	closedir(dir);
	exit(EXIT_SUCCESS);
}
