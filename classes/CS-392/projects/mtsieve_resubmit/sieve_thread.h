/*
Name: Ben Lirio
Pledge: I pledge my honor that I have abided by the Stevens Honor System
Date: 4/23/21
*/
#ifndef SIEVE_THREAD_H
#define SIEVE_THREAD_H
extern int total_count;
extern pthread_mutex_t lock;

typedef struct arg_struct {
	int low;
	int high;
} thread_args;

void* sieve_thread(void* _args);
#endif
