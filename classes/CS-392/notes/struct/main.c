#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define BYTES_PER_WORD 5
#define BITS_PER_BYTE 6

struct byte {
	unsigned char val : BITS_PER_BYTE;
};

struct word {
	unsigned char sign : 1;
	struct byte bytes[BYTES_PER_WORD];
};
struct word newword() {
	struct word temp;
	temp.sign = 0;
	for (int i = 0; i < BYTES_PER_WORD; i++) {
		temp.bytes[i].val = 0;
	}
	return temp;
	
}

int main() {
	int a = 2;
	struct word w = newword();
	printf("%lu\n", sizeof(struct word));
	printf("sign: %d\n", w.sign);
	for (int i = 0; i < BYTES_PER_WORD; i++) {
		w.bytes[i].val = 63;
	}
	for (int i = 0; i < BYTES_PER_WORD; i++) {
		printf("%d ", w.bytes[i].val);
	}
}
