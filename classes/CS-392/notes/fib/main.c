#include <stdio.h>


typedef struct prototype {
	int (*op) (int a, int b);
} prototype;

int op_a(int a, int b);

int main() {
	printf("\n");
	prototype a;
	a.op = op_a;
	printf("%lu\n", sizeof(a.op));
	printf("%d\n", a.op(1,2));
	return 0;
}

int op_a(int a, int b) {
	return a + b;
}
