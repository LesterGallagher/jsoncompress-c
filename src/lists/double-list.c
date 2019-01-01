#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "double-list.h"

double_list_t *double_list_new(unsigned int initialLength) {
    double_list_t *list = (double_list_t*)malloc(sizeof(double_list_t));
    list->array = (double*)malloc(sizeof(double) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void double_list_free(double_list_t *list) {
    free(list->array);
    free(list);
}

void double_list_add(double_list_t *self, double value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(double) * self->allocated);
    }
    self->array[self->count++] = value;
}

double double_list_at_index(double_list_t *self, unsigned int index) {
    return self->array[index];
}

void double_list_trim(double_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(double) * self->allocated);
}




