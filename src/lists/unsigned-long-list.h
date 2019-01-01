#ifndef __UNSIGNED LONG_LIST_H__
#define __UNSIGNED LONG_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct unsigned_long_list {
    unsigned int allocated;
    unsigned int count;
    unsigned long *array;
} unsigned_long_list_t;

unsigned_long_list_t *unsigned_long_list_new(unsigned int initialLength);

void unsigned_long_list_free(unsigned_long_list_t *list);

void unsigned_long_list_add(unsigned_long_list_t *self, unsigned long value);

unsigned long unsigned_long_list_at_index(unsigned_long_list_t *self, unsigned int index);

void unsigned_long_list_trim(unsigned_long_list_t *self);

#endif

