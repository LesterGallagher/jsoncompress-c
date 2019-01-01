#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "bool-ptr-list.h"

bool_ptr_list_t *bool_ptr_list_new(unsigned int initialLength) {
    bool_ptr_list_t *list = (bool_ptr_list_t*)malloc(sizeof(bool_ptr_list_t));
    list->array = (bool**)malloc(sizeof(bool*) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void bool_ptr_list_free(bool_ptr_list_t *list) {
    free(list->array);
    free(list);
}

void bool_ptr_list_add(bool_ptr_list_t *self, bool* value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(bool*) * self->allocated);
    }
    self->array[self->count++] = value;
}

bool* bool_ptr_list_at_index(bool_ptr_list_t *self, unsigned int index) {
    return self->array[index];
}

void bool_ptr_list_trim(bool_ptr_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(bool*) * self->allocated);
}




