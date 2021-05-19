#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	void* handle;
	int (*func)(int, int);
	handle = dlopen("./lib/my_add.so", RTLD_LAZY);
	if (!handle) {
		fprintf(stdout, "Failed to load library. %s.\n", dlerror());
		return EXIT_FAILURE;
	}
	func = dlsym(handle, "add");
	printf("%d + %d = %d\n", 1, 2, func(1,2));
	dlclose(handle);
}
