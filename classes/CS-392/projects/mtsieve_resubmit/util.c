/*
Name: Ben Lirio
Pledge: I pledge my honor that I have abided by the Stevens Honor System
Date: 4/23/21
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "util.h"

void* must_malloc(size_t size) {
	void* ptr = malloc(size);
	if (ptr == NULL) {
		fprintf(stderr, "Error: malloc() failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ptr;
}

void* must_calloc(size_t nmemb, size_t size) {
	void* ptr = calloc(nmemb, size);
	if (ptr == NULL) {
		fprintf(stderr, "Error: calloc1() failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ptr;
}
