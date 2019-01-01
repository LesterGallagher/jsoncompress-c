#ifndef __CHAR_PTR_LIST_H__
#define __CHAR_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct char_ptr_list {
    unsigned int allocated;
    unsigned int count;
    char* *array;
} char_ptr_list_t;

char_ptr_list_t *char_ptr_list_new(unsigned int initialLength);

void char_ptr_list_free(char_ptr_list_t *list);

void char_ptr_list_add(char_ptr_list_t *self, char* value);

char* char_ptr_list_at_index(char_ptr_list_t *self, unsigned int index);

void char_ptr_list_trim(char_ptr_list_t *self);

#endif

