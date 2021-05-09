/*
Name: Ben Lirio
Pledge: I pledge my honor that I have abided by the Stevens Honor System
Date: 4/23/21
*/
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "util.h"
#include "sieve_thread.h"

#define max(X, Y) ((X) > (Y) ? (X) : (Y))
int total_count = 0;
pthread_mutex_t lock;

bool is_prime(int p) {
	int sr = sqrt(p);
	for (int i = 2; i <= sr; i++) {
		if (p%i == 0) {
			return false;
		}
	}
	return true;
}

void* sieve_thread(void* _args) {
	thread_args args = *(thread_args*)_args;
	int a = args.low;
	int b = args.high;
	int sqrt_b = (int) sqrt(b);
	int num_low_primes = max(sqrt_b, 2) + 1;
	bool* low_primes = (bool*)must_malloc(num_low_primes*sizeof(bool));
	memset(low_primes, true, num_low_primes);
	for (int i = 2; i < num_low_primes; i++) {
		if (low_primes[i] == true) {
			for (int j = i*2; j < num_low_primes; j += i) {
				low_primes[j] = false;
			}
		}
	}
	int num_high_primes = b-a+1;
	int high_primes_offset = a;
	bool* high_primes = (bool*)must_malloc(num_high_primes*sizeof(bool));
	memset(high_primes, true, num_high_primes);
	for (int p = 2; p < num_low_primes; p++) {
		if (low_primes[p] == false) {
			continue;
		}
		int i = (a-1) - (a-1)%p + p;
		for (; i <= b; i += p) {
			high_primes[i-high_primes_offset] = false;
		}
	}

	int local_count = 0;
	for (int i = a; i <= b; i++) {
		if (high_primes[i-high_primes_offset] == false) {
			continue;
		}
		if (is_prime(i) == false) {
			printf("%d not be prime\n", i);
		}
		int num_threes = 0;
		for (int j = i; j > 0; j /= 10) {
			int digit = j%10;
			if (digit == 3) {
				num_threes += 1;
			}
		}
		if (num_threes >= 2) {
			local_count++;
		}
	}
	free(low_primes);
	free(high_primes);
	pthread_mutex_lock(&lock);
	total_count += local_count;
	pthread_mutex_unlock(&lock);
	return NULL;
}


