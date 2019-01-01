#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct double_list {
    unsigned int allocated;
    unsigned int count;
    double *array;
} double_list_t;

double_list_t *double_list_new(unsigned int initialLength);

void double_list_free(double_list_t *list);

void double_list_add(double_list_t *self, double value);

double double_list_at_index(double_list_t *self, unsigned int index);

void double_list_trim(double_list_t *self);

#endif

