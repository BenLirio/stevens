#include "big.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8
#define E 2.71828

big_t big_new(bool sign, int offset, unsigned long int val) {
	big_t N;
	N.sign = sign;
	N.offset = offset;
	N.bytes = NULL;
	N.n_bytes = 0;
	while (val > 0) {
		unsigned char mask = -1;
		N.n_bytes = N.n_bytes + 1;
		N.bytes = realloc(N.bytes, N.n_bytes);
		N.bytes[N.n_bytes-1] = val&mask;
		val >>= sizeof(char)*BITS_PER_BYTE;
	}
	return N;
}
void big_delete(big_t N) {
	free(N.bytes);
}
char* big_to_string(big_t N) {
	int CHARS_TO_REP_BYTE = 2 * sizeof(char);
	int NULL_TERMINATOR_SIZE = 1;
	int msg_size = N.n_bytes * CHARS_TO_REP_BYTE;
	char* msg = malloc(msg_size + NULL_TERMINATOR_SIZE);
	for (int i = 0; i < N.n_bytes; i++) {
		for (int j = 0; j < CHARS_TO_REP_BYTE; j++) {
			unsigned char mask = 0x0F << (j*BITS_PER_BYTE/CHARS_TO_REP_BYTE);
			int last_offset = msg_size - 1;
			int offset = last_offset - (i*CHARS_TO_REP_BYTE+j);
			char four_bit_val = (N.bytes[i]&mask)>>(j*BITS_PER_BYTE/CHARS_TO_REP_BYTE);
			if (four_bit_val < 10) {
				msg[offset] = four_bit_val + '0';
			} else {
				msg[offset] = (four_bit_val-10) + 'A';
			}
		}
	}
	msg[msg_size] = '\0';
	return msg;
}
/*
void big_print(big_t N) {
	for (int i = N.n_bytes-1; i >= 0; i--) {
		printf("%.2hhX ", N.bytes[i]);
	}
	printf("\n");
}
void big_set_n_bytes(big_t *N, int n_bytes) {
	N->n_bytes = n_bytes;
	N->bytes = malloc(sizeof(char) * N->n_bytes);
}
error big_set_one(big_t *N) {
	if (N->n_bytes < 1) {
		return TOO_SMALL;
	} else {
		big_set_n_bytes(N, N->n_bytes);
		N->bytes[0] = 1;
	}
	return NIL;
}
comparison big_compare(big_t a, big_t b) {
	int n_bytes = a.n_bytes > b.n_bytes ? a.n_bytes : b.n_bytes;
	for (int i = n_bytes-1; i >= 0; i--) {
		int offset = (sizeof(char) * BITS_PER_BYTE) - 1;
		for (; offset >= 0; offset--) {
			unsigned char mask = 1 << offset;
			int a_has_bit = 0;
			if (a.n_bytes > i && (a.bytes[i]&mask) > 0) {
				a_has_bit = 1;
			}
			int b_has_bit = 0;
			if (b.n_bytes > i && (b.bytes[i]&mask) > 0) {
				b_has_bit = 1;
			}
			if (a_has_bit == b_has_bit) {
				continue;
			}
			if (a_has_bit == 1) {
				return GREATER_THAN;
			}
			return LESS_THAN;
		}

	}
	return EQUAL_TO;
}
error big_copy(big_t *dst, big_t src) {
	if (dst->n_bytes < src.n_bytes) {
		return TOO_SMALL;
	}
	for (int i = 0; i < src.n_bytes; i++) {
		dst->bytes[i] = src.bytes[i];
	}
	return NIL;
}
void big_scale(big_t *N, float factor) {
	unsigned char carry = 0;
	for (int i = 0; i < N->n_bytes; i++) {
		int res = ((N->bytes[i] * factor) + carry + 0.5);
		carry = res >> (sizeof(char) * 8);
		N->bytes[i] = res%0x100;
	}
	if (carry != 0) {
		big_t tmp = big_new();
		big_set_n_bytes(&tmp, N->n_bytes + 1);
		big_copy(&tmp, *N);
		tmp.bytes[tmp.n_bytes-1] = carry;
		big_set_n_bytes(N, tmp.n_bytes);
		big_copy(N, tmp);
	}
}
void big_add(big_t *N, int val) {
	char carry = 0;
	for (int i = 0; i < N->n_bytes; i++) {
		int res = N->bytes[i] + val + carry;
		carry = res >> (sizeof(char) * BITS_PER_BYTE);
		N->bytes[i] = res%0x100;
		if (carry == 0) {
			break;
		}
	}
}


void max_val(big_t *N, int n_bytes) {
	big_set_n_bytes(N, n_bytes);
	for (int i = 0; i < N->n_bytes; i++) {
		N->bytes[i] = 0xFF;
	}
}

void ln(big_t *a, big_t N) {
	big_set_n_bytes(a, 1);
	big_t cur = big_new();
	big_set_n_bytes(&cur, N.n_bytes);
	big_set_one(&cur);
	for (; big_compare(cur, N) == LESS_THAN; big_scale(&cur, E)) {
		big_add(a, 1);
	}
	big_delete(cur);
}
*/
