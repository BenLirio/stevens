/*
Name: Ben Lirio
Pledge: I pledge my honor that I have abided by the Stevens Honor System
Date: 4/23/21
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#include "util.h"
#include "sieve_thread.h"

#define min(X, Y) ((X) < (Y) ? (X) : (Y))
#define INCLUSIVE 1

void usage() {
	fprintf(stderr, "Usage: ./mtsieve -s <starting value> -e <ending value> -t <num threads>\n");
}

int set_up_thread_args(int low, int high, int num_threads_arg,
			thread_args** sieve_args_ptr, pthread_t **sieve_threads_ptr) {

	int range_len = (high - low) + INCLUSIVE;
	int num_threads = min(range_len, num_threads_arg);
	*sieve_args_ptr = (thread_args *) must_calloc(sizeof(struct arg_struct), num_threads);
	*sieve_threads_ptr = (pthread_t *) must_malloc(sizeof(pthread_t)*num_threads);
	int base_thread_range = range_len/num_threads;
	int range_remainder = range_len%num_threads;
	int range_offset = low;
	printf("Finding all prime numbers between %d and %d.\n", low, high);
	printf("%d segment%s:\n", num_threads, num_threads==1 ? "" : "s");
	for (int i = 0; i < num_threads; i++) {
		(*sieve_args_ptr)[i].low = range_offset;
		printf("   [%d, ", range_offset);
		range_offset += base_thread_range;
		range_offset += range_remainder > i ? 1 : 0;
		(*sieve_args_ptr)[i].high = range_offset-1;
		printf("%d]\n", range_offset-1);
	}
	return num_threads;
}

int start_threads(pthread_t* sieve_threads, thread_args* sieve_args, int num_threads) {
	for (int i = 0; i < num_threads; i++) {
		pthread_create(sieve_threads+i, NULL, sieve_thread, sieve_args+i);
	}
	return num_threads;
}
void join_threads(pthread_t* sieve_threads, int num_threads) {
	for (int i = 0; i < num_threads; i++) {
		pthread_join(sieve_threads[i], NULL);
	}
}

enum FLAGS {START=1<<0, END=1<<1, NUM_THREADS=1<<2};
enum ERRORS {INVALID=-1, OVERFLOW=-2};

int char_to_int(char c) {
	int val = c - '0';
	return (val < 10 && val >= 0) ? val : INVALID;
	
}

int ascii_to_int(char* ascii, int* dst) {
	int val = 0;
	int power = 1;
	for(int i = strlen(ascii)-1; i >= 0; i--) {
		if (i == 0 && ascii[i] == '-') {
			val *= -1;
			break;
		}
		int place = char_to_int(ascii[i]);
		if (place == INVALID) {
			*dst = 0;
			return INVALID;
		}
		int prev = val;
		val += place*power;
		if (val < prev) {
			return OVERFLOW;
		}
		power *= 10;
	}
	*dst = val;
	return 0;
}

void parse_error_template(char* optarg, char c, int retval) {
	if (retval == INVALID) {
		fprintf(stderr, "Error: Invalid input '%s' received for parameter '-%c'.\n", optarg, c);
		exit(EXIT_FAILURE);
	} else if (retval == OVERFLOW) {
		fprintf(stderr, "Error: Integer overflow for parameter '-%c'.\n", c);
		exit(EXIT_FAILURE);
	}
}

void must_parse_args(int argc, char* argv[], int* s, int* e, int* t) {
	if (argc == 1) {
		usage();
		exit(EXIT_FAILURE);
	}
	int flags = 0;
	char c;
	int retval;
	opterr = 0;
	int arg_offset = 1;
	while ((c = getopt(argc, argv, ":e:s:t:")) != -1) {
		arg_offset++;
		switch (c) {
		case 'e':
			arg_offset++;
			flags |= END;
			if ((retval = ascii_to_int(optarg, e)) != 0) {
				parse_error_template(optarg, c, retval);
			}
			if (*e < 2) {
				fprintf(stderr, "Error: Ending value must be >= 2.\n");
				exit(EXIT_FAILURE);
			}
			break;
		case 's':
			arg_offset++;
			flags |= START;
			if ((retval = ascii_to_int(optarg, s)) != 0) {
				parse_error_template(optarg, c, retval);
			}
			if (*s < 2) {
				fprintf(stderr, "Error: Starting value must be >= 2.\n");
				exit(EXIT_FAILURE);
			}
			break;
		case 't':
			arg_offset++;
			flags |= NUM_THREADS;
			if ((retval = ascii_to_int(optarg, t)) != 0) {
				parse_error_template(optarg, c, retval);
			}
			break;
		case '?':
			if (optopt == 'e' || optopt == 's' || optopt == 't') {
				fprintf(stderr, "Error: Option -%c requires an argument.\n", optopt);
			} else if (isprint(optopt)) {
				fprintf(stderr, "Error: Unknown option '-%c'.\n", optopt);
			} else {
				fprintf(stderr, "Error: Unknown option character '\\x%x'.\n", optopt);
			}
			exit(EXIT_FAILURE);
		}
	}
	if (argv[arg_offset] != NULL) {
		fprintf(stderr, "Error: Non-option argument '%s' supplied.\n", argv[arg_offset]);
		exit(EXIT_FAILURE);
	}
	if (!(flags&START)) {
		fprintf(stderr, "Error: Required argument <starting value> is missing.\n");
		exit(EXIT_FAILURE);
	}
	if (!(flags&END)) {
		fprintf(stderr, "Error: Required argument <ending value> is missing.\n");
		exit(EXIT_FAILURE);
	}
	if (!(flags&NUM_THREADS)) {
		fprintf(stderr, "Error: Required argument <num value> is missing.\n");
		exit(EXIT_FAILURE);
	}
	if (*e < *s) {
		fprintf(stderr, "Error: Ending value must be >= starting value.\n");
		exit(EXIT_FAILURE);
	}
	if (*t < 1) {
		fprintf(stderr, "Error: Number of threads cannot be less than 1.\n");
		exit(EXIT_FAILURE);
	}
	if (*t > 2*get_nprocs()) {
		fprintf(stderr, "Error: Number of threads cannot exceed twice the number of processors(%d).\n", get_nprocs());
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
	int start;
	int end;
	int num_threads_arg;
	must_parse_args(argc, argv, &start, &end, &num_threads_arg);

	thread_args *sieve_args;
	pthread_t *sieve_threads;
	int num_threads = set_up_thread_args(start, end, num_threads_arg, &sieve_args, &sieve_threads);

	pthread_mutex_init(&lock, NULL);
	int num_threads_started = start_threads(sieve_threads, sieve_args, num_threads);
	join_threads(sieve_threads, num_threads_started);
	pthread_mutex_destroy(&lock);
	free(sieve_threads);
	free(sieve_args);
	printf("Total primes between %d and %d with two or more '3' digits: %d\n", start, end, total_count);

	return 0;
}
