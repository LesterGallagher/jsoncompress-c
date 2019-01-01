#ifndef __CHAR_LIST_H__
#define __CHAR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct char_list {
    unsigned int allocated;
    unsigned int count;
    char *array;
} char_list_t;

char_list_t *char_list_new(unsigned int initialLength);

void char_list_free(char_list_t *list);

void char_list_add(char_list_t *self, char value);

char char_list_at_index(char_list_t *self, unsigned int index);

void char_list_trim(char_list_t *self);

#endif

