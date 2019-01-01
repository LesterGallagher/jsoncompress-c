#ifndef __FLOAT_LIST_H__
#define __FLOAT_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct float_list {
    unsigned int allocated;
    unsigned int count;
    float *array;
} float_list_t;

float_list_t *float_list_new(unsigned int initialLength);

void float_list_free(float_list_t *list);

void float_list_add(float_list_t *self, float value);

float float_list_at_index(float_list_t *self, unsigned int index);

void float_list_trim(float_list_t *self);

#endif

