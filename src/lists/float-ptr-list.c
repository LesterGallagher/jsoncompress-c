#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "float-ptr-list.h"

float_ptr_list_t *float_ptr_list_new(unsigned int initialLength) {
    float_ptr_list_t *list = (float_ptr_list_t*)malloc(sizeof(float_ptr_list_t));
    list->array = (float**)malloc(sizeof(float*) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void float_ptr_list_free(float_ptr_list_t *list) {
    free(list->array);
    free(list);
}

void float_ptr_list_add(float_ptr_list_t *self, float* value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(float*) * self->allocated);
    }
    self->array[self->count++] = value;
}

float* float_ptr_list_at_index(float_ptr_list_t *self, unsigned int index) {
    return self->array[index];
}

void float_ptr_list_trim(float_ptr_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(float*) * self->allocated);
}




