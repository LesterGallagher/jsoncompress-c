#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "long-ptr-list.h"

long_ptr_list_t *long_ptr_list_new(unsigned int initialLength) {
    long_ptr_list_t *list = (long_ptr_list_t*)malloc(sizeof(long_ptr_list_t));
    list->array = (long **)malloc(sizeof(long *) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void long_ptr_list_free(long_ptr_list_t *list) {
    free(list->array);
    free(list);
}

void long_ptr_list_add(long_ptr_list_t *self, long * value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(long *) * self->allocated);
    }
    self->array[self->count++] = value;
}

long * long_ptr_list_at_index(long_ptr_list_t *self, unsigned int index) {
    return self->array[index];
}

void long_ptr_list_trim(long_ptr_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(long *) * self->allocated);
}




