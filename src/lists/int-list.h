#ifndef __INT_LIST_H__
#define __INT_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct int_list {
    unsigned int allocated;
    unsigned int count;
    int *array;
} int_list_t;

int_list_t *int_list_new(unsigned int initialLength);

void int_list_free(int_list_t *list);

void int_list_add(int_list_t *self, int value);

int int_list_at_index(int_list_t *self, unsigned int index);

void int_list_trim(int_list_t *self);

#endif

