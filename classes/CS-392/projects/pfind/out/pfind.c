/*******************************************************************************
 * Name        : pfind.c
 * Author      : Ben Lirio
 * Date        : 03/16/21
 * Description : Pfind main
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>

#include "slice.h"
#include "perm.h"

/*
S_IRUSR owner has read permission
S_IWUSR owner has write permission
S_IXUSR owner has execute permission
S_IRGRP group has read permission
S_IWGRP group has write permission
S_IXGRP group has execute permission
S_IROTH others have read permission
S_IWOTH others have write permission
S_IXOTH others have execute permission
*/
int perm_flags[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

enum flags {DIRECTORY=1<<0, PERMISIONS=1<<1, HELP=1<<2};
void usage(char*);
void walk(string, int);

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
	while((opt = getopt(argc, argv, ":d: :p: :h")) != -1) {
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
		{
			break;
			/*
			printf("%c\n", optopt);
			if (optopt == 'd') {
				fprintf(stderr, "Error: Required argument -d <directory> not found.\n");
			} else if (optopt == 'p') {
				fprintf(stderr, "Error: Required argument -p <permissions string> not found.\n");
			} else {
				printf("%c\n", optopt);
			}
			return EXIT_FAILURE;
			*/
		}
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
		return EXIT_FAILURE;
	}
	if (strlen(perm_str) != 9) {
		fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", perm_str);
		return EXIT_FAILURE;
	}
	int perm_int = parse_perm_str(perm_str);
	char real_path[PATH_MAX];
	realpath(root_dir, real_path);
	string path = new_string();
	path = append(path, real_path);
	if (string_length(path) != 1) {
		path = append(path, "/");
	}
	walk(path, perm_int);
	free_string(path);
	return EXIT_SUCCESS;
}

/*
void walk(string path, int perm_int) {
	DIR *dp 
	if ((dp = opendir(path->head)) == NULL) {
		fprintf(stderr, "Error: Cannot open directory '%s'. %s.\n", path->head, strerror(errno));
		return;
	}
	// Directory open
	struct dirent *de;
	errno = 0;
	int end = path->end;
	struct stat sb;
	while
	closedir(dp);
}
*/

int get_perm_int(struct stat sb) {
	int perm_int = 0;
	for (int i = 0; i < 9; i++) {
		if (sb.st_mode&perm_flags[i]) {
			perm_int += 1<<(8-i);
		}
	}
	return perm_int;
}

int compare_perm(int perm_1, int perm_2, string path) {
	if (perm_1 == perm_2) {
		return 1;
	}
	return 0;
}

void walk(string path, int perm_int){
	DIR *dp = opendir(path->head);
	if (dp == NULL) {
		path->head[strlen(path->head)-1] = '\0';
		fprintf(stderr, "Error: Cannot open directory '%s'. %s.\n", path->head, strerror(errno));
		return;
	}
	struct dirent *de;
	errno = 0;
	int end = path->end;
	struct stat sb;
	while((de = readdir(dp)) != NULL) {
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		path = append(path, de->d_name);
		if (lstat(path->head, &sb) < 0) {
			path = slice_string(path, 0, end);
			continue;
		}
		int file_perm_int = get_perm_int(sb);
		if (compare_perm(file_perm_int, perm_int, path)) {
			printf("%s\n", path->head);
		}
		if (S_ISDIR(sb.st_mode)) {
			int slash_end = path->end;
			path = append(path, "/");
			walk(path, perm_int);
			path = slice_string(path, 0, slash_end);
		}
		path = slice_string(path, 0, end);
	}
	closedir(dp);
	if (errno != 0) {
		//fprintf(stderr, "Error: An error occured while reading the directory %s. %s\n", path->head, strerror(errno));
		return;
	}
}

void usage(char *exec_name) {
	printf("Usage: %s -d <directory> -p <permissions string> [-h]\n", exec_name);
}
