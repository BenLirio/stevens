#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define NUM_LIBRARIES 2

int main() {
	char* imports[NUM_LIBRARIES] = {"./my_dl.so", "./my_dl2.so"};
	void *handles[NUM_LIBRARIES];
	for (int i = 0; i < NUM_LIBRARIES; i++) {
		handles[i] = dlopen(imports[i], RTLD_LAZY);
		if (!handles[i]) {
			fprintf(stderr, "Error: Failed to create handle. %s.\n", dlerror());
			return EXIT_FAILURE;
		}
	}
	int (*add)(int, int);

	*(int**)(&add) = dlsym(handles[0], "add");
	printf("%d + %d = %d\n", 1, 2, add(1, 2));
	*(int**)(&add) = dlsym(handles[1], "add");
	printf("%d + %d = %d\n", 1, 2, add(1, 2));
	dlclose(handles[0]);
	dlclose(handles[1]);
}
