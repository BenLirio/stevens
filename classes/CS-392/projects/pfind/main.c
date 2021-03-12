#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <error.h>
#include <errno.h>

enum flags {DIRECTORY=1<<0, PERMISIONS=1<<1, HELP=1<<2};

void usage(char *exec_name) {
	printf("Usage: %s -d <directory> -p <permissions string> [-h]\n", exec_name);
}

void walk(char *, int perm_int);

int main(int argc, char *argv[]) {
	char* root_dir;
	char* perm_str;
	if (argc <= 1) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	int flags = 0;
	int opt;
	// For some reason ./main -dp sets -d to p and continues on 
	while((opt = getopt(argc, argv, ":d: :p:")) != -1) {
		switch(opt) {
		case 'h':
			flags |= HELP;
			usage(argv[0]);
			return EXIT_SUCCESS;
			continue;
		case 'p':
			flags |= PERMISIONS;
			perm_str = optarg;
			continue;
		case 'd':
			flags |= DIRECTORY;
			root_dir = optarg;
			continue;
		case '?':
			fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
			return EXIT_FAILURE;
		case ':':
			fprintf(stderr, "TODO: Options '-%c' requires an argument", optopt);
			return EXIT_FAILURE;
		default:
			printf("TODO remove default\n");
			return EXIT_FAILURE;
		}
	}
	if ((flags&DIRECTORY) == 0) {
		fprintf(stderr, "Error: Required argument -d <directory> not found.\n");
		return EXIT_FAILURE;
	}
	if ((flags&PERMISIONS) == 0) {
		fprintf(stderr, "Error: Required argument -p <permissions string> not found.\n");
		return EXIT_FAILURE;
	}
	struct stat root_sb;
	if (stat(root_dir, &root_sb) == -1) {
		fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", root_dir, strerror(errno));
	}
	if (strlen(perm_str) != 9) {
		fprintf(stderr, "Error: Permissions string 'pstring' is invalid.");
		return EXIT_FAILURE;
	}
	int perm_int;
	int perm_map[] = {'r', 'w', 'x'};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int idx = i*3 + j;
			if (*(perm_str+idx) == perm_map[j]) {
				perm_int |= 1<<idx;
			} else if(*(perm_str+idx) != '-') {
				fprintf(stderr, "Error: Permissions string'pstring' is invalid.");
			}
		}
	}
	walk(root_dir, perm_int);
	return EXIT_SUCCESS;
}

void walk(char* dirname, int perm_int){
	printf("%s\n", dirname);
}
