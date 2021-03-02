/*******************************************************************************
 * Name        : sort.c
 * Author      : 
 * Date        : 
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      :
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

elem_t get_element_type(int argc, char **argv) {
	elem_t element_type = STRING;
	int opt;
	while ((opt = getopt(argc, argv, ":d :i")) != -1) {
		switch(opt) {
		case 'i':
			element_type = INT;
			break;
		case 'd':
			element_type = DOUBLE;
			break;
		default:
			printf("TODO handle error, wrong flag\n");
			break;
		}
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

int main(int argc, char **argv) {
	elem_t element_type = get_element_type(argc, argv);
	char file_name[128];
	if (element_type != STRING) {
		if (argc == 3) {
			strcpy(file_name, argv[2]);
		}
	} else {
		if (argc == 2) {
			strcpy(file_name, argv[1]);
		}
	}
	char **lines = malloc(sizeof(char*)*MAX_ELEMENTS);
	int num_lines = read_data(file_name, lines);
	size_t elem_sz = 2;
	if (element_type == STRING) {
		char*** array = (char***) malloc(sizeof(char**) * num_lines);
		for (int i = 0; i < num_lines; i++) {
			*(array+i) = (char**) malloc(sizeof(char*));
			*(*(array+i)) = strdup(lines[i]);
		}
		quicksort(array, num_lines, sizeof(char*), str_cmp);
		for (int i = 0; i < num_lines; i++) {
			printf("%s\n", *(*(array+i)));
			free(*(*(array+i)));
			free(*(array+i));
		}
		free(array);
	}
	if (element_type == INT) {
		int** array = (int**) malloc(sizeof(int*) * num_lines);
		for (int i = 0; i < num_lines; i++) {
			*(array+i) = (int*) malloc(sizeof(int));
			**(array+i) = atoi(lines[i]);
		}
		quicksort(array, num_lines, sizeof(int), int_cmp);
		for (int i = 0; i < num_lines; i++) {
			printf("%d\n", **(array+i));
			free(*(array+i));
		}
		free(array);
	}
	if (element_type == DOUBLE) {
		double** array = (double**) malloc(sizeof(double*) * num_lines);
		for (int i = 0; i < num_lines; i++) {
			*(array+i) = (double*) malloc(sizeof(double));
			**(array+i) = atof(lines[i]);
		}
		quicksort(array, num_lines, sizeof(double), dbl_cmp);
		for (int i = 0; i < num_lines; i++) {
			printf("%f\n", **(array+i));
			free(*(array+i));
		}
		free(array);
	}
	for (int i = 0; i < num_lines; i++) {
		free(lines[i]);
	}
	free(lines);
    return EXIT_SUCCESS;
}
