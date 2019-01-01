#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "char-ptr-list.h"

char_ptr_list_t *char_ptr_list_new(unsigned int initialLength) {
    char_ptr_list_t *list = (char_ptr_list_t*)malloc(sizeof(char_ptr_list_t));
    list->array = (char**)malloc(sizeof(char*) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void char_ptr_list_free(char_ptr_list_t *list) {
    free(list->array);
    free(list);
}

void char_ptr_list_add(char_ptr_list_t *self, char* value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(char*) * self->allocated);
    }
    self->array[self->count++] = value;
}

char* char_ptr_list_at_index(char_ptr_list_t *self, unsigned int index) {
    return self->array[index];
}

void char_ptr_list_trim(char_ptr_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(char*) * self->allocated);
}




