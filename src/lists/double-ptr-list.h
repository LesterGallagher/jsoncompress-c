#ifndef __DOUBLE_PTR_LIST_H__
#define __DOUBLE_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct double_ptr_list {
    unsigned int allocated;
    unsigned int count;
    double* *array;
} double_ptr_list_t;

double_ptr_list_t *double_ptr_list_new(unsigned int initialLength);

void double_ptr_list_free(double_ptr_list_t *list);

void double_ptr_list_add(double_ptr_list_t *self, double* value);

double* double_ptr_list_at_index(double_ptr_list_t *self, unsigned int index);

void double_ptr_list_trim(double_ptr_list_t *self);

#endif

