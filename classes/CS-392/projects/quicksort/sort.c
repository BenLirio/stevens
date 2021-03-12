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
#include <fcntl.h>
#include <unistd.h>

// My stuff
#define NULL_POINTER_SIZE 1
// Given
#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024
typedef enum {
    STRING = 1,
    INT = 2,
    DOUBLE = 4
} elem_t;

typedef enum {
	TOO_MANY_ELEMENTS = 1,
} error;


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
void *parse_int(const char *line) {
    int *a = (int*)malloc(sizeof(int));
    *a = atoi(line);
    return a;
}
void *parse_double(const char *line) {
    double *a = (double*)malloc(sizeof(double));
    *a = atof(line);
    return a;
}
void *parse_string(const char *line) {
    return strdup(line);
}

void free_int(void *n) {
    free(n);

}
void free_double(void *n) {
    free(n);
}
void free_string(void *n) {
    free(n);
}

void print_int(void *n) {
    printf("%d\n", *((int*)n));
}
void print_double(void *n) {
    printf("%f\n", *((double*)n));
}
void print_string(void *n) {
    printf("%s\n", (char*)n);
}

int main(int argc, char **argv) {
    printf("Void pointer: %lu\n", sizeof(void*));
    printf("Int pointer: %lu\n", sizeof(int*));
    printf("Double pointer: %lu\n", sizeof(double*));
	int op;
	elem_t element_type = 0;
	while ((op = getopt(argc, argv, ":i :d")) != -1) {
		switch(op) {
		case 'i':
			element_type |= INT;
			break;
		case 'd':
            element_type |= DOUBLE;
			break;
		}
	}
    if (element_type == 0)
        element_type |= STRING;

    char file_name[128];
    void *(*parse_func)(const char*);
    void (*free_func)(void*);
    void (*print_func)(void*);
    switch(element_type) {
    case DOUBLE:
        strcpy(file_name, "test_data_double");
        parse_func = parse_double;
        print_func = print_double;
        free_func = free_double;
        break;
    case INT:
        strcpy(file_name, "test_data_int");
        parse_func = parse_int;
        print_func = print_int;
        free_func = free_int;
        break;
    case STRING:
        strcpy(file_name, "test_data_string");
        parse_func = parse_string;
        free_func = free_string;
        print_func = print_string;
        break;
    default:
        printf("%d\n", element_type);
        printf("WRONG FLAG ERROR!\n");
        return 1;
    }
    // TODO open input file
	
    // TODO Allocate space in char** for at least MAX_ELEMENTS
    size_t num_bytes = MAX_ELEMENTS * sizeof(char*);
    char **lines = malloc(num_bytes);
    // Read each line to char**
	int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        printf("FILE DOES NOT EXIST");
        return 1;
    }
	char buf[20];
	int nbytes = 20;
	ssize_t n;
	int cur_line = 0;
	int cur_line_offset = 0;
	for (;;) {
		n = read(fd, buf, nbytes);
		if (n == 0) {
			break;
		}
		for (int i = 0; i < n; i++) {
			if (buf[i] == '\n') {
				lines[cur_line++][cur_line_offset] = '\0';
				cur_line_offset = 0;
				if (cur_line > MAX_ELEMENTS) {
					return TOO_MANY_ELEMENTS;
				}
			} else {
                if (cur_line_offset == 0) {
                    lines[cur_line] = malloc(MAX_STRLEN + NULL_POINTER_SIZE);
                }
				lines[cur_line][cur_line_offset++] = buf[i];
			}
		}
	}
	size_t num_lines = cur_line;
    // Create Array
    void **data = malloc(sizeof(char*) * num_lines);
    for (int i = 0; i < num_lines; i++) {
        data[i] = parse_func(lines[i]);
    }
    // Free Lines
    for (int i = 0; i < num_lines; i++) {
		free(*(lines+i));
    }
	free(lines);
    // Close File
	int err = close(fd);
    // Call quicksort
	quicksort(&data, num_lines, sizeof(void*), str_cmp);
    // Free Data
    for (int i = 0; i < num_lines; i++) {
        print_func(*(data+i));
    }
    for (int i = 0; i < num_lines; i++) {
        free_func(data[i]);
    }
    free(data);
    return EXIT_SUCCESS;
}
// Read lines to string
// Parse lines to void*
// Free lines read
// Quicksort lines
// Free data
