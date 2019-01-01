#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "int-list.h"

int_list_t *int_list_new(unsigned int initialLength) {
    int_list_t *list = (int_list_t*)malloc(sizeof(int_list_t));
    list->array = (int*)malloc(sizeof(int) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void int_list_free(int_list_t *list) {
    free(list->array);
    free(list);
}

void int_list_add(int_list_t *self, int value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(int) * self->allocated);
    }
    self->array[self->count++] = value;
}

int int_list_at_index(int_list_t *self, unsigned int index) {
    return self->array[index];
}

void int_list_trim(int_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(int) * self->allocated);
}




