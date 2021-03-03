/*******************************************************************************
 * Name        : quicksort.h
 * Author      : 
 * Date        : 
 * Description : Quicksort header.
 * Pledge      :
 ******************************************************************************/
/**
 * TODO - put all non-static function prototypes from quicksort.c inside
 * wrapper #ifndef.
 */
#ifndef QUICK_SORT_H
#define QUICK_SORT_H
int str_cmp(const void *a, const void *b);
int int_cmp(const void *a, const void *b);
int dbl_cmp(const void *a, const void *b);
void quicksort(void *array, size_t len, size_t elem_sz,
               int (*comp) (const void*, const void*));

#endif /* QUICK_SORT_H */
