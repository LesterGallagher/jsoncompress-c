#ifndef __SHORT_PTR_LIST_H__
#define __SHORT_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct short_ptr_list {
    unsigned int allocated;
    unsigned int count;
    short * *array;
} short_ptr_list_t;

short_ptr_list_t *short_ptr_list_new(unsigned int initialLength);

void short_ptr_list_free(short_ptr_list_t *list);

void short_ptr_list_add(short_ptr_list_t *self, short * value);

short * short_ptr_list_at_index(short_ptr_list_t *self, unsigned int index);

void short_ptr_list_trim(short_ptr_list_t *self);

#endif

