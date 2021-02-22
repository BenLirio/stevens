#include "big.h"
#include <stdio.h>
#include <stdlib.h>

#define COMPLEMENT_OFFSET 1
#define BITS_PER_BYTE 8
#define E 2.71828

static void big_set_n_bytes(big_t *N, int n_bytes) {
	N->n_bytes = n_bytes;
	N->bytes = realloc(N->bytes, N->n_bytes);
}

static void validate_input(bool sign, int offset, unsigned long int val) {
	if (val == 0 && (sign == false || offset != 0)) {
		if (sign == false)
			printf("Panic: Creating a big with val = 0, and sign = false is not allowed");
		if (offset != 0)
			printf("Panic: Creating a big with val = 0, and offset != 0 is not allowed");
		exit(1);
	}
}

big_t big_new() {
	big_t N;
	N.sign = true;
	N.offset = 0;
	N.n_bytes = 0;
	N.bytes = NULL;
	return N;
}

void big_set(big_t *N, bool sign, int offset, unsigned long int val) {
	validate_input(sign, offset, val);
	N->sign = sign;
	N->offset = offset;
	if (N->sign == false) {
		val -= 1;
	}
	while (val > 0) {
		unsigned char byte;
		int mask = 0xFF;
		byte = val&mask;
		big_set_n_bytes(N, N->n_bytes + 1);
		N->bytes[N->n_bytes-1] = N->sign ? byte : ~byte;
		val >>= BITS_PER_BYTE;
	}
}

void big_delete(big_t N) {
	free(N.bytes);
}

long double big_to_double(big_t N) {
	long double cur = 0;
	for (int i = 0; i < N.n_bytes; i++) {
		long double multiplier = 1<<(i*BITS_PER_BYTE);
		unsigned char byte = N.bytes[i];
		byte = N.sign ? byte : ~byte;
		cur += byte * multiplier;
	}
	cur = N.sign ? cur : (-cur - COMPLEMENT_OFFSET);
	long double exponent = N.offset > 0 ? 1<<N.offset : 1<<(-N.offset);
	cur = N.offset > 0 ? cur*exponent : cur/exponent;
	return cur;
}

void big_add(big_t *C, big_t A, big_t B) {
	*C = big_new();
	int carry = 0;

	int min_offset = A.offset < B.offset ? A.offset : B.offset;
	C->offset = min_offset;
	int i = min_offset;
	while (true) {
		bool A_valid_range = false;
		bool B_valid_range = false;
		int A_pos = i - A.offset;
		int B_pos = i - B.offset;
		if (A_pos >= 0 && A_pos < A.n_bytes)
			A_valid_range = true;
		if (B_pos >= 0 && B_pos < B.n_bytes)
			B_valid_range = true;
		if (A_valid_range == false && B_valid_range == false)
			break;
		int A_val = (A.sign == true) ? 0x00 : 0xFF;
		int B_val = (B.sign == true) ? 0x00 : 0xFF;
		if (A_valid_range == true)
			A_val = A.bytes[A_pos];
		if (B_valid_range == true)
			B_val = B.bytes[B_pos];
		int C_pos = A_pos < B_pos ? A_pos : B_pos;
		int val = A_val + B_val + carry;
		carry = val>>BITS_PER_BYTE;
		val = val&0xFF;
		big_set_n_bytes(C, C->n_bytes + 1);
		C->bytes[i-min_offset] = val;
		i++;
	}
	if (A.sign && B.sign && carry) {
		big_set_n_bytes(C, C->n_bytes + 1);
		C->bytes[C->n_bytes-1] = 1;
		return;
	} 
	if (!A.sign && !B.sign && carry) {
		C->sign = false;
		return;
	}
	if (!A.sign && !B.sign && !carry) {
		C->sign = false;
		big_set_n_bytes(C, C->n_bytes + 1);
		C->bytes[C->n_bytes-1] = 0xFE;
		return;
	}
	C->sign = !((!A.sign + !B.sign + carry)%2);
}


/*
void big_flip_sign(big_t *N) {
	bool is_zero = true;
	for (int i = 0; i < N->n_bytes; i++) {
		if (N->bytes[i] != 0x00) {
			is_zero = false;
		}
	}
	if (is_zero) {
		printf("Panic: You can not flip signs of a zero\n");
		exit(1);
	}
	if (N->sign == true) {
		int carry = 1;
		for (int i = 0; carry && i < N->n_bytes; i++) {
			int val = N->bytes[i] - 1;
			carry = val>>BITS_PER_BYTE;
			val = val&0xFF;
			N->bytes[i] = val;
		}
		if (carry) {
			big_increment_n_bytes(N);
			N->bytes[N->n_bytes-1] = 0xFE;
		}
	}
	N->sign = !N->sign;
	for (int i = 0; i < N->n_bytes; i++) {
		N->bytes[i] = ~(N->bytes[i]);
	}
	if (N->sign == true) {
		int carry = 1;
		for (int i = 0; carry && i < N->n_bytes; i++) {
			int val = N->bytes[i] + 1;
			carry = val>>BITS_PER_BYTE;
			val = val&0xFF;
			N->bytes[i] = val;
		}
		if (carry) {
			big_increment_n_bytes(N);
			N->bytes[N->n_bytes-1] = 0xFE;
		}
	}
}

void big_multiply(big_t *C, big_t A, big_t B) {
	bool A_sign = true;
	bool B_sign = true;
	if (!A.sign) {
		A_sign = false;
		big_flip_sign(&A);
	}
	if (!B.sign) {
		B_sign = false;
		big_flip_sign(&B);
	}
	*C = big_new(true, 0, 0);
	int carry = 0;

	int min_offset = A.offset < B.offset ? A.offset : B.offset;
	C->offset = min_offset;
	int i = min_offset;
	while (true) {
		bool A_valid_range = false;
		bool B_valid_range = false;
		int A_pos = i - A.offset;
		int B_pos = i - B.offset;
		if (A_pos >= 0 && A_pos < A.n_bytes)
			A_valid_range = true;
		if (B_pos >= 0 && B_pos < B.n_bytes)
			B_valid_range = true;
		if (A_valid_range == false && B_valid_range == false)
			break;
		int A_val = 0x01;
		int B_val = 0x01;
		if (A_valid_range == true)
			A_val = A.bytes[A_pos];
		if (B_valid_range == true)
			B_val = B.bytes[B_pos];
		int C_pos = A_pos < B_pos ? A_pos : B_pos;
		int val = A_val *  B_val + carry;
		carry = val>>BITS_PER_BYTE;
		val = val&0xFF;
		big_increment_n_bytes(C);
		C->bytes[C_pos] = val;
		i++;
	}
	if (carry) {
		big_increment_n_bytes(C);
		C->bytes[C->n_bytes-1] = carry;
	}
	if (A_sign != B_sign)
		big_flip_sign(C);
}
*/
