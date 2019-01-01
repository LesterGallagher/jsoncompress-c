#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "short-list.h"

short_list_t *short_list_new(unsigned int initialLength) {
    short_list_t *list = (short_list_t*)malloc(sizeof(short_list_t));
    list->array = (short*)malloc(sizeof(short) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void short_list_free(short_list_t *list) {
    free(list->array);
    free(list);
}

void short_list_add(short_list_t *self, short value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(short) * self->allocated);
    }
    self->array[self->count++] = value;
}

short short_list_at_index(short_list_t *self, unsigned int index) {
    return self->array[index];
}

void short_list_trim(short_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(short) * self->allocated);
}




