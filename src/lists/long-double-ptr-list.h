#ifndef __LONG DOUBLE_PTR_LIST_H__
#define __LONG DOUBLE_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct long_double_ptr_list {
    unsigned int allocated;
    unsigned int count;
    long double* *array;
} long_double_ptr_list_t;

long_double_ptr_list_t *long_double_ptr_list_new(unsigned int initialLength);

void long_double_ptr_list_free(long_double_ptr_list_t *list);

void long_double_ptr_list_add(long_double_ptr_list_t *self, long double* value);

long double* long_double_ptr_list_at_index(long_double_ptr_list_t *self, unsigned int index);

void long_double_ptr_list_trim(long_double_ptr_list_t *self);

#endif

