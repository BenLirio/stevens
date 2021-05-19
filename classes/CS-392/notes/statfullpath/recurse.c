#include <stdio.h>
#include <dirent.h>
#include <string.h>

void listFilesRecursively(char*);
int main() {
	char path[100] = "/home/ben/src/github.com/BenLirio/TAOCP";

	listFilesRecursively(path);

	return 0;
}

void listFilesRecursively(char *basePath) {
	char path[1000][1000];
	struct dirent *dp;
	DIR *dir = opendir(basePath);

	if (!dir)
		return;

	int num_paths = 0;
	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			strcpy(path[num_paths], basePath);
			strcat(path[num_paths], "/");
			strcat(path[num_paths], dp->d_name);
			num_paths++;
		}
	}
	for (int i = 0; i < num_paths; i++) {
		listFilesRecursively(path[i]);
	}
	printf("%s\n", basePath);
}
