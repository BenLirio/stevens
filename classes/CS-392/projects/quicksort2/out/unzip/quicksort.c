/*******************************************************************************
 * Name        : sort.c
 * Author      : Ben Lirio
 * Date        : 3/2/21
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "quicksort.h"


/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*comp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*comp) (const void*, const void*));


/**
 * Compares two integers passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to int pointers.
 * Returns:
 * -- 0 if the integers are equal
 * -- a positive number if the first integer is greater
 * -- a negative if the second integer is greater
 */
int int_cmp(const void *a, const void *b) {
	return *(int*)a > *(int*)b;
}

/**
 * Compares two doubles passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to double pointers.
 * Returns:
 * -- 0 if the doubles are equal
 * -- 1 if the first double is greater
 * -- -1 if the second double is greater
 */
int dbl_cmp(const void *a, const void *b) {
	return *(double*)a > *(double*)b;
}

/**
 * Compares two char arrays passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to char* pointers (i.e. char**).
 * Returns the result of calling strcmp on them.
 */
int str_cmp(const void *a, const void *b) { 
	const char *a_string = *(const char**)a;
	const char *b_string = *(const char**)b;
	int rtn = strcmp(a_string, b_string);
	return rtn;
}

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to character types and works with them as char
 * pointers for the remainder of the function.
 * Swaps one byte at a time, until all 'size' bytes have been swapped.
 * For example, if ints are passed in, size will be 4. Therefore, this function
 * swaps 4 bytes in a and b character pointers.
 */
static void swap(void *a, void *b, size_t size) {
	char *a_cast = (char*)a;
	char *b_cast = (char*)b;
	for(int i = 0; i < size; i++) {
		char tmp = *(a_cast+i);
		*(a_cast+i) = *(b_cast+i);
		*(b_cast+i) = tmp;
	}
}

/**
 * Partitions array around a pivot, utilizing the swap function.
 * Each time the function runs, the pivot is placed into the correct index of
 * the array in sorted order. All elements less than the pivot should
 * be to its left, and all elements greater than or equal to the pivot should be
 * to its right.
 * The function pointer is dereferenced when it is used.
 * Indexing into void *array does not work. All work must be performed with
 * pointer arithmetic.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*comp) (const void*, const void*)) {
	int pivot = right;
	void **data = (void**)array;

	int i = left-1;
	for (int j = left; j < right; j++) {
		int cmp = comp(*(data+pivot), *(data+j));
		if (cmp > 0) {
			i++;
			swap(*(data+i), *(data+j), elem_sz);
		}
	}
	swap(*(data+i+1), *(data+right), elem_sz);
	return (i+1);
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*comp) (const void*, const void*)) {
	if (left < right) {
		int pivot = lomuto(array, left, right, elem_sz, comp);
		quicksort_helper(array, pivot+1, right, elem_sz, comp);
		quicksort_helper(array, left, pivot-1, elem_sz, comp);
	}
}

/**
 * Quicksort function exposed to the user.
 * Calls quicksort_helper with left = 0 and right = len - 1.
 */
void quicksort(void *array, size_t len, size_t elem_sz,
               int (*comp) (const void*, const void*)) {
	quicksort_helper(array, 0, len-1, elem_sz, comp);
}
