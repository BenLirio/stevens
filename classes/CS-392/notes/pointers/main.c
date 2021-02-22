#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))


typedef union my_union {
	char c;
	short s;
	int i;
} my_union_t;

void display(my_union_t u) {
	printf("%c\n", u.c);
	printf("%d\n", u.s);
	printf("%d\n", u.i);
}

void display_line(unsigned int num_bytes) {
	putchar('+');
	for (int i = num_bytes * 8 - 1; i>= 0; i--) {
		putchar('-');
		if (i % 8 == 0) {
			putchar('+');
		}
	}
	putchar('\n');
}

void display_bits(my_union_t u) {
	unsigned int
		p,
		num_bytes = MIN(sizeof(my_union_t), sizeof(unsigned int));
	memcpy(&p, &u, num_bytes);
	display_line(num_bytes);
	putchar('|');
	unsigned int mask;
	for (int i = num_bytes * 8 - 1; i >= 0; i--) {
		mask = 1 << i;
		if (p & mask) {
			putchar('1');
		} else {
			putchar('0');
		}
		if (i % 8 == 0) {
			putchar('|');
		}
	}
	putchar('\n');
	display_line(num_bytes);
}

int main() {
	my_union_t u;
	u.c = 'A';
	u.i = 1 << 31;
	u.c = 'b';
	display_bits(u);
	return 0;
}
