#ifndef __UNSIGNED SHORT_LIST_H__
#define __UNSIGNED SHORT_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct unsigned_short_list {
    unsigned int allocated;
    unsigned int count;
    unsigned short *array;
} unsigned_short_list_t;

unsigned_short_list_t *unsigned_short_list_new(unsigned int initialLength);

void unsigned_short_list_free(unsigned_short_list_t *list);

void unsigned_short_list_add(unsigned_short_list_t *self, unsigned short value);

unsigned short unsigned_short_list_at_index(unsigned_short_list_t *self, unsigned int index);

void unsigned_short_list_trim(unsigned_short_list_t *self);

#endif

