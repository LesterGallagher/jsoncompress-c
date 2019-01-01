#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef __stringbuilder_H__
#define __stringbuilder_H__

typedef struct stringbuilder {
    unsigned int allocated;
    unsigned int length;
    char *array;
} stringbuilder_t;

stringbuilder_t *stringbuilder_new(unsigned int initialLength);

void stringbuilder_free(stringbuilder_t *list);

void stringbuilder_add(stringbuilder_t *self, char value);

void stringbuilder_concat(stringbuilder_t *self, char *str, unsigned int len);

char stringbuilder_at_index(stringbuilder_t *self, unsigned int index);

void stringbuilder_trim(stringbuilder_t *self);

#endif

