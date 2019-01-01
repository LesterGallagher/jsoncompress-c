#ifndef __FLOAT_PTR_LIST_H__
#define __FLOAT_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct float_ptr_list {
    unsigned int allocated;
    unsigned int count;
    float* *array;
} float_ptr_list_t;

float_ptr_list_t *float_ptr_list_new(unsigned int initialLength);

void float_ptr_list_free(float_ptr_list_t *list);

void float_ptr_list_add(float_ptr_list_t *self, float* value);

float* float_ptr_list_at_index(float_ptr_list_t *self, unsigned int index);

void float_ptr_list_trim(float_ptr_list_t *self);

#endif

