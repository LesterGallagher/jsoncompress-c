#ifndef __LONG_LIST_H__
#define __LONG_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct long_list {
    unsigned int allocated;
    unsigned int count;
    long *array;
} long_list_t;

long_list_t *long_list_new(unsigned int initialLength);

void long_list_free(long_list_t *list);

void long_list_add(long_list_t *self, long value);

long long_list_at_index(long_list_t *self, unsigned int index);

void long_list_trim(long_list_t *self);

#endif

