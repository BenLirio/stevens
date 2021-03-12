#include <stdio.h>

void swap(void *a, void *b, size_t size) {
	while (size--) {
		char tmp = *(char*)a;
		*(char*)a++ = *(char*)b;
		*(char*)b++ = tmp;
	}
}

int main() {
	double a = 999999.09123;
	double b = 0;
	printf("a=%f b=%f\n", a, b);
	swap(&a, &b, sizeof(double));
	printf("a=%f b=%f\n", a, b);
}
