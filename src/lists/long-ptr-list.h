#ifndef __LONG_PTR_LIST_H__
#define __LONG_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct long_ptr_list {
    unsigned int allocated;
    unsigned int count;
    long * *array;
} long_ptr_list_t;

long_ptr_list_t *long_ptr_list_new(unsigned int initialLength);

void long_ptr_list_free(long_ptr_list_t *list);

void long_ptr_list_add(long_ptr_list_t *self, long * value);

long * long_ptr_list_at_index(long_ptr_list_t *self, unsigned int index);

void long_ptr_list_trim(long_ptr_list_t *self);

#endif

