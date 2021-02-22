#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef union my_union {
	char c;
	short s;
	int i;
} my_union_t;

/**
 * Displays the values of the union's members.
 */
void display(my_union_t u) {
	printf("%c\n", u.c);
	printf("%c\n", u.s);
	printf("%c\n", u.i);
}

void display_line(unsigned int num_bytes) {
	putchar('+');
	for (int i = num_bytes * 8 - 1; i >= 0; i--) {
		putchar('-');
		if (i % 8 == 0) {
			putchar('+');
		}
	}
	putchar('\n');
}

/**
 * Converts the union into an unsigned int and performs bitwise operations
 * to display the contents of memeory occupied by the union.
 */
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
		mask >>= 1;
	}
	putchar('\n');
	display_line(num_bytes);
}

int main() {
	my_union_t u;
	int var0;

	u.i = 0;
	display(u);

	u.c = 'A';
	display(u);

	u.s = 16383;
	display(u);

	var0 = u.c;
	printf("%d\n", u.c); // why is u.c -1?
	printf("%d\n", var0); // why is u.c -1?

	display_bits(u);
	return 0;
}
