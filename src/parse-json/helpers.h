#include <stdbool.h>
#include "json-parser.h"

#ifndef __JSON_PARSER_HELPERS_H__
#define __JSON_PARSER_HELPERS_H__

#define INDENTATION_SPACES 4

json_node_t *json_get_prop(json_node_t *kvn, char *key_name);

json_node_t *json_parse_file(char *filename);

json_node_t *json_deep_clone(json_node_t* node);

int json_print_tree(json_node_t *root, unsigned short is_compact);

int json_free(json_node_t *node);

char* json_get_type_name(json_type type);

bool json_verify_integrity(json_node_t *node);

json_node_t *json_node_new(json_type type, char *key, json_node_t *parent);

#endif



