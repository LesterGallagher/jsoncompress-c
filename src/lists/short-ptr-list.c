#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "short-ptr-list.h"

short_ptr_list_t *short_ptr_list_new(unsigned int initialLength) {
    short_ptr_list_t *list = (short_ptr_list_t*)malloc(sizeof(short_ptr_list_t));
    list->array = (short **)malloc(sizeof(short *) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void short_ptr_list_free(short_ptr_list_t *list) {
    free(list->array);
    free(list);
}

void short_ptr_list_add(short_ptr_list_t *self, short * value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(short *) * self->allocated);
    }
    self->array[self->count++] = value;
}

short * short_ptr_list_at_index(short_ptr_list_t *self, unsigned int index) {
    return self->array[index];
}

void short_ptr_list_trim(short_ptr_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(short *) * self->allocated);
}




