#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "json-node-ptr-list.h"

json_node_ptr_list_t *json_node_ptr_list_new(unsigned int initialLength) {
    json_node_ptr_list_t *list = (json_node_ptr_list_t*)malloc(sizeof(json_node_ptr_list_t));
    list->array = (json_node_t**)malloc(sizeof(json_node_t*) * initialLength);
    list->allocated = initialLength;
    list->count = 0;
    list->offset = 0;
    return list;
}

void json_node_ptr_list_free(json_node_ptr_list_t *list) {
    free(list->array);
    free(list);
}

void json_node_ptr_list_add(json_node_ptr_list_t *self, json_node_t* value) {
    if (self->offset + self->count >= self->allocated) {
        self->allocated *= 2;
        self->array = realloc(self->array, sizeof(json_node_t*) * self->allocated);
    }
    self->array[self->offset + self->count++] = value;
}

json_node_t* json_node_ptr_list_at_index(json_node_ptr_list_t *self, unsigned int index) {
    return self->array[self->offset + index];
}

void json_node_ptr_list_trim(json_node_ptr_list_t *self) {
    if (self->allocated == self->count) return;
    self->allocated = self->count;
    self->array = realloc(self->array, sizeof(json_node_t*) * self->allocated);
}

json_node_ptr_list_t *json_node_ptr_list_clone(json_node_ptr_list_t *self) {
    json_node_ptr_list_t *new = json_node_ptr_list_new(self->count);
    new->count = self->count;
    new->allocated = self->count;
    new->offset = 0;
    memcpy(
        new->array, 
        self->array, 
        self->count * sizeof(json_node_t*));
    return new;
}

void json_node_ptr_list_sort(json_node_ptr_list_t *self, json_node_ptr_list_sort_cb_t sort_cb) {
    int (*func_ptr)(const void*, const void*);
    func_ptr = (int (*)(const void*, const void*))sort_cb;

    qsort(
        self->array + self->offset * sizeof(json_node_t*), 
        self->count, 
        sizeof(json_node_t*), 
        func_ptr);
}

