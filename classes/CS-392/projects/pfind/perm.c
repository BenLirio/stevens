#include <stdio.h>
#include <stdlib.h>

int parse_perm_str(const char* perm_str) {
	int perm_map[] = {'r', 'w', 'x'};
	int perm_int = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int idx = i*3 + j;
			if (*(perm_str+idx) == perm_map[j]) {
				perm_int |= 1<<(8-idx);
			} else if(*(perm_str+idx) != '-') {
				fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", perm_str);
				exit(EXIT_FAILURE);
			}
		}
	}
	return perm_int;
}
