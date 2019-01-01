#ifndef __SHORT_LIST_H__
#define __SHORT_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct short_list {
    unsigned int allocated;
    unsigned int count;
    short *array;
} short_list_t;

short_list_t *short_list_new(unsigned int initialLength);

void short_list_free(short_list_t *list);

void short_list_add(short_list_t *self, short value);

short short_list_at_index(short_list_t *self, unsigned int index);

void short_list_trim(short_list_t *self);

#endif

