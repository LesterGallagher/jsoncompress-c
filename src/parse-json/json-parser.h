#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_KEY_SIZE 1024

struct json_node_ptr_list;

typedef enum { JSON_NUMBER, JSON_NULL, JSON_STRING, JSON_BOOL, JSON_ARRAY, JSON_OBJECT } json_type;

typedef union json_value {
    bool bool_val;
    char* string_val;
    double num_val;
    struct json_node_ptr_list *nodes_val;
} json_value_t;

typedef struct json_node {
    json_type type;
    json_value_t value;
    char* key;
    struct json_node *parent;
} json_node_t;

#include "json-node-ptr-list.h"

json_node_t *json_parse(char *json_buf);

char *json_stringify(json_node_t *json_node);

#endif

