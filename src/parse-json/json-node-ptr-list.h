#ifndef __JSON_NODE_PTR_LIST_H__
#define __JSON_NODE_PTR_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "json-parser.h"

typedef struct json_node_ptr_list {
    unsigned int allocated;
    unsigned int count;
    unsigned int offset;
    json_node_t* *array;
} json_node_ptr_list_t;

typedef int json_node_ptr_list_sort_cb_t(const json_node_t **a, const json_node_t **b);

typedef int sort_func_t(const void* a, const void* b);

typedef int cb(const void*, const void*);

json_node_ptr_list_t *json_node_ptr_list_new(unsigned int initialLength);

void json_node_ptr_list_free(json_node_ptr_list_t *list);

void json_node_ptr_list_add(json_node_ptr_list_t *self, json_node_t* value);

json_node_t* json_node_ptr_list_at_index(json_node_ptr_list_t *self, unsigned int index);

void json_node_ptr_list_trim(json_node_ptr_list_t *self);

json_node_ptr_list_t *json_node_ptr_list_clone(json_node_ptr_list_t *self);

void json_node_ptr_list_sort(json_node_ptr_list_t *self, json_node_ptr_list_sort_cb_t sort_cb);

#endif


