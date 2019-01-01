#ifndef __BOOL_LIST_H__
#define __BOOL_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct bool_list {
    unsigned int allocated;
    unsigned int count;
    bool *array;
} bool_list_t;

bool_list_t *bool_list_new(unsigned int initialLength);

void bool_list_free(bool_list_t *list);

void bool_list_add(bool_list_t *self, bool value);

bool bool_list_at_index(bool_list_t *self, unsigned int index);

void bool_list_trim(bool_list_t *self);

#endif

