#include "big.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 32

struct test_case {
	bool sign;
	int offset;
	unsigned long int val;
};
typedef struct test_case test_case;
test_case test_cases[NUM_TESTS] = {
	// Trivial Examples
	{true, 0, 0},
	{false, 0, 0},
	{true, 1, 0},
	{false, 1, 0},
	{true, -1, 0},
	{false, -1, 0},
	{true, 0, 1},
	{false, 0, 1},
	{true, 1, 1},
	{false, 1, 1},
	{true, -1, 1},
	{false, -1, 1},
	// Large Simple
	{true, 0, 255},
	{false, 0, 255},
	{true, 0, 12345},
	{false, 0, 12345},
	{true, 0, 425118932},
	{false, 0, 425118932},
	// Exponents
	{true, 10, 1},
	{false, 10, 1},
	{true, 22, 1},
	{false, 22, 1},
	{true, -10, 1},
	{false, -10, 1},
	{true, -22, 1},
	{false, -22, 1},
	// Complex
	{true, 3, 531},
	{true, -3, 531},
	{false, 3, 531},
	{false, -3, 531},
	{true, 8, 1234321},
	{true, -8, 1234321},
};

void test_big_new() {
	printf("test_big_new:\n");
	big_t N;
	for (int i = 0; i < NUM_TESTS; i++) {
		test_case t = test_cases[i];
		N = big_new(t.sign, t.offset, t.val);
		if (N.sign != t.sign)
			printf("Expected sign to be %d, got %d\n", t.sign, N.sign);
		if (N.offset != t.offset)
			printf("Expected offset to be %d, got %d\n", t.offset, N.offset);
		
		big_delete(N);
	}
}

void test_big_to_double() {
	printf("test_big_to_double:\n");
	big_t N;
	for (int i = 0; i < NUM_TESTS; i++) {
		test_case t = test_cases[i];
		N = big_new(t.sign, t.offset, t.val);
		long double N_double = big_to_double(N);
		long double val = t.val;
		if (t.sign == false)
			val *= -1;
		if (t.offset < 0) {
			for (int j = 0; j < -t.offset; j++) {
				val *= .5;
			}
		} else {
			for (int j = 0; j < t.offset; j++) {
				val *= 2;
			}
		}
		if (N_double != val) {
			printf("sign:\t\t%d\n", t.sign);
			printf("offset:\t\t%d\n", t.offset);
			printf("val:\t\t%lu\n", t.val);
			printf("test_computed:\t%Lf\n", val);
			printf("N_double:\t%Lf\n", N_double);
			printf("\n");
		}
		big_delete(N);
	}
}

void test_big_to_string() {
	printf("test_big_to_stirng:\n");
	big_t N = big_new(true, 0, 255);
	char* msg = big_to_string(N);
	for (int i = 0; i < strlen(msg); i++) {
		if (msg[i] != 'F') {
			printf("Expected msg[%d] to equal F, got %c\n", i, msg[i]);
		}
	}
	free(msg);
	big_delete(N);
}


void test_big_add() {
	big_t a, b, c;

	a = big_new(true, 0, 1);
	b = big_new(true, 0, 2);
	big_add(&c, a, b);
	if (big_to_double(c) != 3) {
		printf("%s\n", big_to_string(c));
		printf("Expected c to equal 3, got %Lf\n", big_to_double(c));
	}
	big_delete(a);
	big_delete(b);
	big_delete(c);

	a = big_new(false, 0, 1);
	b = big_new(false, 0, 2);
	big_add(&c, a, b);
	if (big_to_double(c) != -1) {
		printf("%s\n", big_to_string(c));
		printf("Expected c to equal -1, got %Lf\n", big_to_double(c));
	}
	big_delete(a);
	big_delete(b);
	big_delete(c);

}

int main() {
	test_big_new();
	test_big_to_double();
	//test_big_to_string();
}
