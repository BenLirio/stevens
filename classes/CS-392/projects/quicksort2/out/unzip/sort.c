/*******************************************************************************
 * Name        : sort.c
 * Author      : Ben Lirio
 * Date        : 3/2/21
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

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

void usage();

elem_t get_element_type(int argc, char **argv);

/**
 * CREDIT: read_data from canvas
 * Reads data from filename into an already allocated 2D array of chars.
 * Exits the entire program if the file cannot be opened.
 */
size_t read_data(char *filename, char **data);

int get_file_name_index(int argc, elem_t element_type);

void *parse_str(void* dst, char* line);
void *parse_int(void* dst, char* line);
void *parse_dbl(void* dst, char* line);

void free_str(void* a);
void free_int(void* a);
void free_dbl(void* a);

void print_str(void* a);
void print_int(void* a);
void print_dbl(void* a);

int element_sizes[3] = {sizeof(char*), sizeof(int), sizeof(double)};
int (*cmp_funcs[3])(const void*, const void*) = {str_cmp, int_cmp, dbl_cmp};
void (*free_funcs[3])(void*) = {free_str, free_int, free_dbl};
void (*print_funcs[3])(void*) = {print_str, print_int, print_dbl};
void *(*parse_funcs[3])(void*, char*) = {parse_str, parse_int, parse_dbl};

int main(int argc, char **argv) {
	// Error: CASE 1
	if (argc <= 1) {
		usage();
		exit(EXIT_FAILURE);
	}
	elem_t element_type = get_element_type(argc, argv);
	int file_name_index = get_file_name_index(argc, element_type);
	char file_name[128];
	strcpy(file_name, argv[file_name_index]);

	char **lines = malloc(sizeof(char*)*MAX_ELEMENTS);
	int num_lines = read_data(file_name, lines);

	void** array = (void**)malloc(sizeof(void*) * num_lines);
	for (int i = 0; i < num_lines; i++) {
		*(array+i) = parse_funcs[element_type](*(array+i), lines[i]);
	}
	quicksort(array, num_lines, element_sizes[element_type], cmp_funcs[element_type]);
	for (int i = 0; i < num_lines; i++) {
		print_funcs[element_type](*(array+i));
		free_funcs[element_type](*(array+i));
	}
	free(array);
	for (int i = 0; i < num_lines; i++) {
		free(lines[i]);
	}
	free(lines);
    return EXIT_SUCCESS;
}

void usage() {
	printf("Usage ./sort [-i|-d] filename \
	\n\t-i: Specifies the file contains ints.\
	\n\t-d: Specifies the file contains doubles.\
	\n\tfilename: The file to sort.\
	\n\tNo flags defaults to sorting strings.\n");
}

elem_t get_element_type(int argc, char **argv) {
	elem_t element_type = STRING;
	int opt;
	int i = 0;
	while ((opt = getopt(argc, argv, ":d :i")) != -1) {
		i++;
		switch(opt) {
		case 'i':
			element_type = INT;
			break;
		case 'd':
			element_type = DOUBLE;
			break;
		case '?':
		default:
			// Error: Case 2
			fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
			usage();
			exit(EXIT_FAILURE);
			break;
		}
	}
	if (i > 1) {
		// Error: Case 6
		fprintf(stderr, "Error: Too many flags specified.\n");
		exit(EXIT_FAILURE);
	}
	return element_type;
}

/**
 * CREDIT: read_data from canvas
 * Reads data from filename into an already allocated 2D array of chars.
 * Exits the entire program if the file cannot be opened.
 */
size_t read_data(char *filename, char **data) {
    // Open the file.
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
		// Error: Case 3
        fprintf(stderr, "Error: Cannot open '%s'. %s.\n", filename,
                strerror(errno));
        free(data);
        exit(EXIT_FAILURE);
    }
// Read in the data.
    size_t index = 0;
    char str[MAX_STRLEN + 2];
    char *eoln;
    while (fgets(str, MAX_STRLEN + 2, fp) != NULL) {
        eoln = strchr(str, '\n');
        if (eoln == NULL) {
            str[MAX_STRLEN] = '\0';
        } else {
            *eoln = '\0';
        }
        // Ignore blank lines.
        if (strlen(str) != 0) {
            data[index] = (char *)malloc((MAX_STRLEN + 1) * sizeof(char));
            strcpy(data[index++], str);
        }
    }

    // Close the file before returning from the function.
    fclose(fp);

    return index;
}

void test_argc() {

}

int get_file_name_index(int argc, elem_t element_type) {
	int base_argc = 1;
	int num_flags = element_type == STRING ? 0 : 1;
	int files_passed = argc - num_flags - base_argc;

	if (files_passed < 1) {
		// Error: Case 4
		fprintf(stderr, "Error: No input file specified.\n");
		exit(EXIT_FAILURE);
	}
	if (files_passed > 1) {
		// Error: Case 5
		fprintf(stderr, "Error: Too many files specified.\n");
		exit(EXIT_FAILURE);
	}

	int file_name_index = base_argc + num_flags;
	return file_name_index;
}

/*
 * Parsing functions
 */
void *parse_str(void* dst, char* line) {
	char** dst_cast = (char**) dst;
	dst_cast = (char**) malloc(sizeof(char*));
	*dst_cast = strdup(line);
	return dst_cast;
}
void *parse_int(void* dst, char* line) {
	int* dst_cast = (int*) dst;
	dst_cast = (int*) malloc(sizeof(int));
	*dst_cast = atoi(line);
	return dst_cast;
}
void *parse_dbl(void* dst, char* line) {
	double* dst_cast = (double*) dst;
	dst_cast = (double*) malloc(sizeof(double));
	*dst_cast = atof(line);
	return dst_cast;
}

/*
 * Free functions
 */
void free_str(void* a) {
	char** a_cast = (char**)a;
	free(*a_cast);
	free(a_cast);
}
void free_int(void* a) {
	int* a_cast = (int*)a;
	free(a_cast);
}
void free_dbl(void* a) {
	double* a_cast = (double*)a;
	free(a_cast);
}

/*
 * Print functions
 */
void print_str(void* a) {
	char** a_cast = (char**)a;
	printf("%s\n", *a_cast);
}
void print_int(void* a) {
	int* a_cast = (int*)a;
	printf("%d\n", *a_cast);
}
void print_dbl(void* a) {
	double* a_cast = (double*)a;
	printf("%f\n", *a_cast);
}

