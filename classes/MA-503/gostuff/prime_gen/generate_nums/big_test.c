#include "big.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 27

struct test_case {
	bool sign;
	int offset;
	unsigned long int val;
};
typedef struct test_case test_case;
test_case test_cases[NUM_TESTS] = {
	// Trivial Examples
	{false, 0, 1},
	{true, 0, 0},
	{true, 0, 1},
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
	big_t N = big_new();
	big_delete(N);
}

void test_big_set() {
	printf("test_big_set:\n");
	big_t N;
	for (int i = 0; i < NUM_TESTS; i++) {
		test_case t = test_cases[i];
		N = big_new();
		big_set(&N, t.sign, t.offset, t.val);
		if (N.sign != t.sign && t.val != 0)
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
		N = big_new();
		big_set(&N, t.sign, t.offset, t.val);
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
			big_delete(N);
			break;
		}
		big_delete(N);
	}
}


void test_big_add() {
	printf("test_big_add:\n");
	for (int i = 0; i < NUM_TESTS; i++) {
		test_case ta = test_cases[i];
		big_t A = big_new();
		big_set(&A, ta.sign, ta.offset, ta.val);
		long double A_double = big_to_double(A);
		for (int j = 0; j < NUM_TESTS; j++) {
			test_case tb = test_cases[j];
			big_t B = big_new();
			big_set(&B, tb.sign, tb.offset, tb.val);
			long double B_double = big_to_double(B);

			big_t C;
			big_add(&C, A, B);
			long double C_double = big_to_double(C);
			if (C_double != (A_double + B_double)) {
				printf("Expected %.2Lf + %.2Lf = %.2Lf, got %.2Lf\n", A_double, B_double, A_double+B_double, C_double);
				big_delete(C);
				big_delete(A);
				big_delete(B);
				goto BAD_CASE;
				
			}

			big_delete(C);
			big_delete(B);
		}
		big_delete(A);
	}
BAD_CASE:{}
}

/*
void test_big_flip_sign() {
	printf("test_big_flip_sign:\n");
	for (int i = 0; i < NUM_TESTS; i++) {
		test_case t = test_cases[i];
		if (t.val == 0)
			continue;
		big_t N = big_new(t.sign, t.offset, t.val);
		long double N_double = big_to_double(N);
		big_flip_sign(&N);
		long double N_double_flipped = big_to_double(N);
		if (N_double != -N_double_flipped) {
			printf("Expected %.2Lf * -1 = %.2Lf\n", N_double, N_double_flipped);
		}

		big_delete(N);
	}
}

void test_big_multiply() {
	printf("test_big_multiply:\n");
	for (int i = 0; i < NUM_TESTS; i++) {
		test_case ta = test_cases[i];
		big_t A = big_new(ta.sign, ta.offset, ta.val);
		long double A_double = big_to_double(A);
		for (int j = 0; j < NUM_TESTS; j++) {
			test_case tb = test_cases[j];
			big_t B = big_new(tb.sign, tb.offset, tb.val);
			long double B_double = big_to_double(B);

			big_t C;
			big_multiply(&C, A, B);
			long double C_double = big_to_double(C);
			if (C_double != (A_double * B_double)) {
				printf("----\n");
				printf("ta.val = %lu\n", ta.val);
				printf("tb.val = %lu\n", tb.val);
				printf("Expected %.2Lf * %.2Lf = %.2Lf, got %.2Lf\n", A_double, B_double, A_double*B_double, C_double);
				big_delete(C);
				big_delete(A);
				big_delete(B);
				goto BAD_CASE;
				
			}

			big_delete(C);
			big_delete(B);
		}
		big_delete(A);
	}
BAD_CASE:{}
}

*/
int main() {
	test_big_new();
	test_big_set();
	test_big_to_double();
	//test_big_flip_sign();
	test_big_add();
	//test_big_multiply();
}
