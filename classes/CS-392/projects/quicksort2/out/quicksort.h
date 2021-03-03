/*******************************************************************************
 * Name        : sort.c
 * Author      : Ben Lirio
 * Date        : 3/2/21
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#ifndef QUICK_SORT_H
#define QUICK_SORT_H
int str_cmp(const void *a, const void *b);
int int_cmp(const void *a, const void *b);
int dbl_cmp(const void *a, const void *b);
void quicksort(void *array, size_t len, size_t elem_sz,
               int (*comp) (const void*, const void*));

#endif /* QUICK_SORT_H */
