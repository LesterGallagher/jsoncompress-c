#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "unsigned-long-list.h"

unsigned_long_list_t *unsigned_long_list_new(unsigned int initialLength) {
    unsigned_long_list_t *list = (unsigned_long_list_t*)malloc(sizeof(unsigned_long_list_t));
    list->array = (unsigned long*)malloc(sizeof(unsigned long) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void unsigned_long_list_free(unsigned_long_list_t *list) {
    free(list->array);
    free(list);
}

void unsigned_long_list_add(unsigned_long_list_t *self, unsigned long value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(unsigned long) * self->allocated);
    }
    self->array[self->count++] = value;
}

unsigned long unsigned_long_list_at_index(unsigned_long_list_t *self, unsigned int index) {
    return self->array[index];
}

void unsigned_long_list_trim(unsigned_long_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(unsigned long) * self->allocated);
}




