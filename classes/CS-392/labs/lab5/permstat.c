/*******************************************************************************
 * Name        : permstat.h
 * Author      : Ben Lirio
 * Date        : 3/12/21
 * Description : Implements permission_string
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define NUM_PERM_SECTIONS 3
int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR,
               S_IRGRP, S_IWGRP, S_IXGRP,
               S_IROTH, S_IWOTH, S_IXOTH};

#define NUM_PERM_TYPES 3
char perms_char_code[] = {'r', 'w', 'x'};
void display_usage(char *progname) {
    printf("Usage: %s <filename>\n", progname);
}

/**
 * TODO
 * Returns a string (pointer to char array) containing the permissions of the
 * file referenced in statbuf.
 * Allocates enough space on the heap to hold the 10 printable characters.
 * The first char is always a - (dash), since all files must be regular files.
 * The remaining 9 characters represent the permissions of user (owner), group,
 * and others: r, w, x, or -.
 */
char* permission_string(struct stat *statbuf) {
	int dst_len = NUM_PERM_SECTIONS*NUM_PERM_TYPES + 1; // +1 for initial -
	char *dst = malloc(sizeof(char)*(dst_len+1)); // +1 for null terminator

	dst[0] = '-';
	int offset = 1; // initial char is a -
	for (int i = 0; i < NUM_PERM_SECTIONS; i++) {
		for (int j = 0; j < NUM_PERM_TYPES; j++) {
			int idx = 3*i + j;
			if (statbuf->st_mode & perms[idx]) {
				dst[idx+offset] = perms_char_code[j];
			} else {
				dst[idx+offset] = '-';
			}
		}
	}

	dst[dst_len] = '\0';
	return dst;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        display_usage(argv[0]);
        return EXIT_FAILURE;
    }

    struct stat statbuf;
    if (stat(argv[1], &statbuf) < 0) {
        fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", argv[1],
                strerror(errno));
        return EXIT_FAILURE;
    }

	/* TODO
	 * If the argument supplied to this program is not a regular file,
	 * print out an error message to standard error and return EXIT_FAILURE.
	 * For example:
	 * $ ./permstat iamdir
	 * Error: 'iamdir' is not a regular file.
	 */
	if ((statbuf.st_mode & S_IFREG) != S_IFREG) {
		fprintf(stderr, "Error: '%s' is not a regular file.\n", argv[1]);
		return EXIT_FAILURE;
	}


    char *perms = permission_string(&statbuf);
    printf("Permissions: %s\n", perms);
    free(perms);

    return EXIT_SUCCESS;
	
}
