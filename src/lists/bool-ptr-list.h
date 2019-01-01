#ifndef __BOOL_PTR_LIST_H__
#define __BOOL_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct bool_ptr_list {
    unsigned int allocated;
    unsigned int count;
    bool* *array;
} bool_ptr_list_t;

bool_ptr_list_t *bool_ptr_list_new(unsigned int initialLength);

void bool_ptr_list_free(bool_ptr_list_t *list);

void bool_ptr_list_add(bool_ptr_list_t *self, bool* value);

bool* bool_ptr_list_at_index(bool_ptr_list_t *self, unsigned int index);

void bool_ptr_list_trim(bool_ptr_list_t *self);

#endif

