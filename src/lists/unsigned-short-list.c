#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "unsigned-short-list.h"

unsigned_short_list_t *unsigned_short_list_new(unsigned int initialLength) {
    unsigned_short_list_t *list = (unsigned_short_list_t*)malloc(sizeof(unsigned_short_list_t));
    list->array = (unsigned short*)malloc(sizeof(unsigned short) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void unsigned_short_list_free(unsigned_short_list_t *list) {
    free(list->array);
    free(list);
}

void unsigned_short_list_add(unsigned_short_list_t *self, unsigned short value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(unsigned short) * self->allocated);
    }
    self->array[self->count++] = value;
}

unsigned short unsigned_short_list_at_index(unsigned_short_list_t *self, unsigned int index) {
    return self->array[index];
}

void unsigned_short_list_trim(unsigned_short_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(unsigned short) * self->allocated);
}




