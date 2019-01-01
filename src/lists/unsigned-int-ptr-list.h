#ifndef __UNSIGNED INT_PTR_LIST_H__
#define __UNSIGNED INT_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct unsigned_int_ptr_list {
    unsigned int allocated;
    unsigned int count;
    unsigned int* *array;
} unsigned_int_ptr_list_t;

unsigned_int_ptr_list_t *unsigned_int_ptr_list_new(unsigned int initialLength);

void unsigned_int_ptr_list_free(unsigned_int_ptr_list_t *list);

void unsigned_int_ptr_list_add(unsigned_int_ptr_list_t *self, unsigned int* value);

unsigned int* unsigned_int_ptr_list_at_index(unsigned_int_ptr_list_t *self, unsigned int index);

void unsigned_int_ptr_list_trim(unsigned_int_ptr_list_t *self);

#endif

