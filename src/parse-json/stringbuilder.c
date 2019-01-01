#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "stringbuilder.h"

stringbuilder_t *stringbuilder_new(unsigned int initialLength) {
    stringbuilder_t *self = (stringbuilder_t*)malloc(sizeof(stringbuilder_t));
    self->array = (char*)malloc(sizeof(char) * initialLength + 1);
    self->allocated = initialLength + 1;
    self->length = 0;
    self->array[0] = '\0';
    return self;
}

void stringbuilder_free(stringbuilder_t *self) {
    free(self->array);
    free(self);
}

void stringbuilder_concat(stringbuilder_t *self, char *str, unsigned int len) {
    while (self->length + (len + 1) >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(char) * self->allocated);
    }
    memcpy(self->array + self->length * sizeof(char), str, (len + 1) * sizeof(char));
    self->length += len;
}

void stringbuilder_add(stringbuilder_t *self, char value) {
    if (self->length + 1 >= self->allocated) {
        self->array = realloc(self->array, sizeof(char) * self->allocated * 2);
    }
    self->array[self->length++] = value;
    self->array[self->length] = '\0';
}

char stringbuilder_at_index(stringbuilder_t *self, unsigned int index) {
    return self->array[index];
}

void stringbuilder_trim(stringbuilder_t *self) {
    if (self->allocated == self->length) return;
    self->allocated = self->length;
    self->array = realloc(self->array, self->allocated);
}




