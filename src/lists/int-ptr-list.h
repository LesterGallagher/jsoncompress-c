#ifndef __INT_PTR_LIST_H__
#define __INT_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct int_ptr_list {
    unsigned int allocated;
    unsigned int count;
    int * *array;
} int_ptr_list_t;

int_ptr_list_t *int_ptr_list_new(unsigned int initialLength);

void int_ptr_list_free(int_ptr_list_t *list);

void int_ptr_list_add(int_ptr_list_t *self, int * value);

int * int_ptr_list_at_index(int_ptr_list_t *self, unsigned int index);

void int_ptr_list_trim(int_ptr_list_t *self);

#endif

