/*******************************************************************************
 * Name        : sort.c
 * Author      : Ben Lirio
 * Date        : 2/24/21
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define NULL_POINTER_SIZE 1
#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

typedef enum {
    STRING,
    INT,
    DOUBLE
} elem_t;

/**
 * Basic structure of sort.c:
 *
 * Parses args with getopt.
 * Opens input file for reading.
 * Allocates space in a char** for at least MAX_ELEMENTS strings to be stored,
 * where MAX_ELEMENTS is 1024.
 * Reads in the file
 * - For each line, allocates space in each index of the char** to store the
 *   line.
 * Closes the file, after reading in all the lines.
 * Calls quicksort based on type (int, double, string) supplied on the command
 * line.
 * Frees all data.
 * Ensures there are no memory leaks with valgrind. 
 */
int main(int argc, char **argv) {
    return EXIT_SUCCESS;

    // TODO open input file
    char file_name[] = "test_data";


    // TODO Allocate space in char** for at least MAX_ELEMENTS
    size_t num_bytes = MAX_ELEMENTS * sizeof(char*);
    char **lines = malloc(num_bytes);
    for (int i = 0; i < MAX_ELEMENTS; i++) {
	*(lines+i) = malloc(MAX_STRLEN + NULL_POINTER_SIZE);
    }
    // Read each line to char**
    // Close File
    // Call quicksort
    // Free Data
}
