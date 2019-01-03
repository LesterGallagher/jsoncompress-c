
#include "helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../CMemLeak.h"

json_node_t *json_get_prop(json_node_t *branch_root, char *key_name) {
    if (branch_root->type != JSON_OBJECT) return NULL;
    for (unsigned int i = 0; i < branch_root->value.nodes_val->count; i++) {
        if (branch_root->value.nodes_val != NULL) { // todo: not neccesary ?
            json_node_t *child = json_node_ptr_list_at_index(branch_root->value.nodes_val, i);
            if (strcmp(child->key, key_name) == 0) {
                return child;
            }
        }
    }
    return NULL;
}

char* json_get_type_name(json_type type) {
    switch(type) {
        case JSON_ARRAY: return "array";
        case JSON_BOOL: return "boolean";
        case JSON_NULL: return "null";
        case JSON_NUMBER: return "number";
        case JSON_OBJECT: return "object";
        case JSON_STRING: return "string";
        default: return NULL;
    }
}

bool json_verify_integrity(json_node_t *node) {
    (void)(node);
    printf("json_verify_integrity is not yet implemented\n");
    return true;
}

json_node_t *json_parse_file(char *filename) {
    char *str = NULL;
    long length;
    FILE *f = fopen(filename, "r");
    if (f == NULL) return NULL;
    else {
        if (fseek(f, 0, SEEK_END)) return NULL;
        length = ftell(f);
        if (fseek(f, 0, SEEK_SET)) return NULL;
        str = malloc(length + sizeof(char));
        if (str) fread(str, 1, length, f);
        else return NULL;
        str[length] = '\0';
        if (fclose(f)) return NULL;
    }
    json_node_t *root = json_parse(str);
    free(str);
    return root;
}

int json_print_tree_rec(json_node_t *elem, unsigned short scope) {
    static const char *strings[] = {"number", "null", "string", "boolean", "array", "object"};
    if (elem->key != NULL && strlen(elem->key) > 0)
    {
        if (scope > 0) printf("%*c", scope * INDENTATION_SPACES, ' ');
        printf("key: %s\n", elem->key);
    }
    if (scope > 0)
        printf("%*c", scope * INDENTATION_SPACES, ' ');
    printf("type: %s\n", strings[elem->type]);
    if (elem->type == JSON_NULL)
    {
        if (scope > 0) printf("%*c", scope * INDENTATION_SPACES, ' ');
        printf("value: null\n");
    }
    else if (elem->type == JSON_BOOL)
    {
        if (scope > 0) printf("%*c", scope * INDENTATION_SPACES, ' ');
        printf("value: %s\n", elem->value.bool_val ? "true" : "false");
    }
    else if (elem->type == JSON_STRING)
    {
        if (scope > 0) printf("%*c", scope * INDENTATION_SPACES, ' ');
        printf("value: %s\n", elem->value.string_val);
    }
    else if (elem->type == JSON_NUMBER)
    {
        if (scope > 0) printf("%*c", scope * INDENTATION_SPACES, ' ');
        printf("value: %.6f\n", elem->value.num_val);
    }
    else if (elem->type == JSON_OBJECT || elem->type == JSON_ARRAY)
    {
        if (scope > 0) printf("%*c", scope * INDENTATION_SPACES, ' ');
        printf("value:\n");
        for (unsigned int i = 0; i < elem->value.nodes_val->count; i++) {
            json_node_t *child = json_node_ptr_list_at_index(elem->value.nodes_val, i);
            json_print_tree_rec(child, scope + 1);
        }
    }
    return 0;
}

json_node_t *json_deep_clone(json_node_t *node) {
    size_t json_node_size = sizeof(json_node_t);
    json_node_t *new_node = malloc(json_node_size);
    memcpy(new_node, node, json_node_size);
    if (new_node->key != NULL) new_node->key = strdup(node->key);
    if (node->type == JSON_STRING) {
        new_node->value.string_val = strdup(node->value.string_val);
    } else if (node->type == JSON_ARRAY || node->type == JSON_OBJECT) {
        new_node->value.nodes_val = json_node_ptr_list_new(node->value.nodes_val->count);
        for(unsigned int i = 0; i < node->value.nodes_val->count; i++) {
            json_node_t *child = json_node_ptr_list_at_index(node->value.nodes_val, i);
            json_node_t *cloned_child = json_deep_clone(child);
            json_node_ptr_list_add(new_node->value.nodes_val, cloned_child);
            cloned_child->parent = new_node;
        }
    }
    return new_node;
}

int print_compact_key_value_tree_rec(json_node_t *elem, unsigned short scope) {
    if (elem->key != NULL && strlen(elem->key) > 0)
    {
        if (scope > 0) printf("%*c", scope * INDENTATION_SPACES, ' ');
        printf("%s: ", elem->key);
    }
    if (elem->type == JSON_NULL)
        printf("null\n");
    else if (elem->type == JSON_BOOL)
        printf("%s\n", elem->value.bool_val ? "true" : "false");
    else if (elem->type == JSON_STRING)
        printf("%s\n", elem->value.string_val);
    else if (elem->type == JSON_NUMBER)
        printf("%.6f\n", elem->value.num_val);
    else if (elem->type == JSON_OBJECT || elem->type == JSON_ARRAY)
    {
        puts("");
        for (unsigned int i = 0; i < elem->value.nodes_val->count; i++) {
            json_node_t *child = json_node_ptr_list_at_index(elem->value.nodes_val, i);
            if (child != NULL) {
                print_compact_key_value_tree_rec(child, scope + 1);
            } else {
                puts("Child is null... Something is not right. Continueing...");
            }
        }
    }
    return 0;
}

int json_print_tree(json_node_t *root, unsigned short is_compact) {
    is_compact ? print_compact_key_value_tree_rec(root, 0) : json_print_tree_rec(root, 0);
    return 0;
}

int json_free(json_node_t *node) {
    if (node->type == JSON_OBJECT || node->type == JSON_ARRAY) {
        for (unsigned int i = 0; i < node->value.nodes_val->count; i++) {
            json_node_t *child = json_node_ptr_list_at_index(node->value.nodes_val, i);
            if (child != NULL) {
                json_free(child);
                free(child);
            } else {
                puts("Child is null... Something is not right. Continueing...");
            }
        }
    } else if (node->type == JSON_STRING) {
        if (node->value.string_val != NULL) {
            free(node->value.string_val);
        }
        else {
            puts("Node string value should never be null. Please set the json_type to JSON_NULL instead of setting the string value to null..");
        }
    }
    if (node->key != NULL) {
        free(node->key);
    } else {
        puts("Node key should never be null..");
    }
    if (node->parent == NULL) {
        free(node);
    }
    return 0;
}

json_node_t *json_node_new(json_type type, char *key, json_node_t *parent) {
    json_node_t *new_node = malloc(sizeof(json_node_t));
    new_node->type = type;
    new_node->key = strdup(key);
    new_node->parent = parent;
    if (type == JSON_OBJECT || type == JSON_ARRAY) new_node->value.nodes_val = json_node_ptr_list_new(8);
    return new_node;
}

