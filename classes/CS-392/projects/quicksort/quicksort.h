/*******************************************************************************
 * Name        : quicksort.h
 * Author      : Ben Lirio
 * Date        : 2/22/21
 * Description : Quicksort header.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
/**
 * TODO - put all non-static function prototypes from quicksort.c inside
 * wrapper #ifndef.
 */

#ifndef _QUICK_SORT_H
#define _QUICK_SORT_H
void quicksort(void *array, size_t len, size_t elem_sz,
               int (*comp) (const void*, const void*));

int str_cmp(const void *a, const void *b);
    
#endif
