#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "unsigned-int-ptr-list.h"

unsigned_int_ptr_list_t *unsigned_int_ptr_list_new(unsigned int initialLength) {
    unsigned_int_ptr_list_t *list = (unsigned_int_ptr_list_t*)malloc(sizeof(unsigned_int_ptr_list_t));
    list->array = (unsigned int**)malloc(sizeof(unsigned int*) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    return list;
}

void unsigned_int_ptr_list_free(unsigned_int_ptr_list_t *list) {
    free(list->array);
    free(list);
}

void unsigned_int_ptr_list_add(unsigned_int_ptr_list_t *self, unsigned int* value) {
    if (self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(unsigned int*) * self->allocated);
    }
    self->array[self->count++] = value;
}

unsigned int* unsigned_int_ptr_list_at_index(unsigned_int_ptr_list_t *self, unsigned int index) {
    return self->array[index];
}

void unsigned_int_ptr_list_trim(unsigned_int_ptr_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(unsigned int*) * self->allocated);
}




