#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* fib_thread(void*);

void* fib_thread(void* ptr) {
	int* n = malloc(sizeof(int));
	*n = *(int*)ptr;
	if (*n <= 1) {
		return (void*)n;
	}
	pthread_t fib_1;
	pthread_t fib_2;

	int* fib_1_n = malloc(sizeof(int));
	*fib_1_n = *n - 1;
	pthread_create(&fib_1, NULL, fib_thread, (void*)fib_1_n);
	int* fib_2_n = malloc(sizeof(int));
	*fib_2_n = *n - 2;
	pthread_create(&fib_2, NULL, fib_thread, (void*)fib_2_n);
	
	int* rtn_1 = malloc(sizeof(int));
	pthread_join(fib_1, (void**)&rtn_1);
	int* rtn_2 = malloc(sizeof(int));
	pthread_join(fib_2, (void**)&rtn_2);
	int* rtn = malloc(sizeof(int));
	*rtn = *rtn_1 + *rtn_2;
	return (void*)rtn;
}

int main() {
	for (int i = 0;; i++) {
		pthread_t t1;
		int* n = malloc(sizeof(int));
		*n = i;
		pthread_create(&t1, NULL, fib_thread, (void*) n);

		int* rtn = malloc(sizeof(int));
		pthread_join(t1, (void**)&rtn);
		printf("fib(%d) = %d\n", *n, *rtn);
	}
}
