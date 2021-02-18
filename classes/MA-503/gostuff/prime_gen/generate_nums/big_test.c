#include "big.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_big_new() {
	printf("test_big_new:\n");
	bool sign = false;
	int offset = -10;
	unsigned long int val = 256;
	big_t N;
	N = big_new(sign, offset, val);
	if (N.sign != sign) {
		printf("Expected N's sign to be %d, got %d\n (true?)", sign, N.sign);
	}
	if (N.offset != offset) {
		printf("Expected offset to be %d, got %d\n", offset, N.offset);
	}
	if (N.n_bytes != 2) {
		printf("Expected n_bytes to be %d, got %d\n", 2, N.n_bytes);
	}
	if (N.bytes[0] != 0) {
		printf("Expect bytes[0] to be 0, got %d\n", N.bytes[0]);
	}
	if (N.bytes[1] != 1) {
		printf("Expect bytes[1] to be 1, got %d\n", N.bytes[1]);
	}
	big_delete(N);
}

void test_big_to_string() {
	printf("test_big_to_stirng:\n");
	big_t N = big_new(true, 0, 256*256*255);
	char* msg = big_to_string(N);
	printf("len: %lu\n", strlen(msg));
	for (int i = 0; i < strlen(msg); i++) {
		printf("%c", msg[i]);
	}
	printf("\n");
	free(msg);
	big_delete(N);
}

int main() {
	test_big_new();
	test_big_to_string();
}
