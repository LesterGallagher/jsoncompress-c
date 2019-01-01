#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "long-double-list.h"

long_double_list_t *long_double_list_new(unsigned int initialLength) {
    long_double_list_t *list = (long_double_list_t*)malloc(sizeof(long_double_list_t));
    list->array = (long double*)malloc(sizeof(long double) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void long_double_list_free(long_double_list_t *list) {
    free(list->array);
    free(list);
}

void long_double_list_add(long_double_list_t *self, long double value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(long double) * self->allocated);
    }
    self->array[self->count++] = value;
}

long double long_double_list_at_index(long_double_list_t *self, unsigned int index) {
    return self->array[index];
}

void long_double_list_trim(long_double_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(long double) * self->allocated);
}




