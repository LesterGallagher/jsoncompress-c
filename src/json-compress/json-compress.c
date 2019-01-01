#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../CMemLeak.h"
#include "../parse-json/helpers.h"
#include "../parse-json/json-parser.h"
#include "../parse-json/json-node-ptr-list.h"
#include "json-compress.h"
#include "../hexdump.h"

static char num[10];

int sort(const json_node_t **a, const json_node_t **b) {
    return strcmp((*a)->key, (*b)->key);
}

json_node_t *do_compression(json_node_t *json, json_node_t *schema);

bool json_type_is_incompatible(char* type1, char* type2) {
    return strcmp(type1, type2) != 0 && !((strcmp(type1, "integer") == 0 && strcmp(type2, "number") == 0)
        || (strcmp(type1, "number") == 0 && strcmp(type2, "integer") == 0));
}

json_node_t *parse_prop(json_node_t *prop, json_node_t *val) {
    (void)(prop);
    (void)(val);
    json_node_t *type_node = json_get_prop(prop, "type");
    char* type = type_node->value.string_val;
    if (json_type_is_incompatible(json_get_type_name(val->type), type)) {
        printf("JSON Schema: \"%s\" incorrect type", prop->key);
        getchar();
        exit(1); // todo: error codes
    } else if (strcmp(type, "array") == 0) {
        json_node_t *arr = malloc(sizeof(json_node_t));
        arr->value.nodes_val = json_node_ptr_list_new(val->value.nodes_val->count);
        arr->type = JSON_ARRAY;
        arr->key = NULL;
        arr->parent = NULL;
        json_node_t *schema_items = json_get_prop(prop, "items");
        for(unsigned int i = 0; i < val->value.nodes_val->count; i++) {
            json_node_t *input_child = json_node_ptr_list_at_index(val->value.nodes_val, i);
            json_node_t *child = parse_prop(schema_items, input_child);
            sprintf((char*)num, "%i", i);
            child->key = strdup((char*)num);
            child->parent = arr;
            json_node_ptr_list_add(arr->value.nodes_val, child);
        }
        return arr;
    } else if (strcmp(type, "object") == 0) {
        return do_compression(val, prop);
    } else { // STRING, NUMBER, BOOL, NULL
        json_node_t *clone = malloc(sizeof(json_node_t));
        memcpy(clone, val, sizeof(json_node_t));
        clone->key = NULL;
        clone->parent = NULL;
        if (val->type == JSON_STRING) clone->value.string_val = strdup(val->value.string_val);
        return clone;
    }
}

json_node_t *do_compression(json_node_t *json, json_node_t *schema) {
    json_node_t *properties = json_get_prop(schema, "properties");

    if (properties == NULL || properties->type != JSON_OBJECT) {
        printf("JSON Schema should have a \"properties\" key with type \"object\".\n");
        exit(1); // todo: error codes
    }

    if (json->value.nodes_val->count != properties->value.nodes_val->count) {
        printf("Amount of JSON schema properties does not equal the amount of actual properties.\n");
        printf("The amount of properties needs to be the same for the algorithm to work.\n");
        printf("Consider passing in \"null\" instead of removing the key from an object.\n");
        exit(1); // todo: error codes
    }

    json_node_t *ret = malloc(sizeof(json_node_t));
    json_node_ptr_list_t *list = json_node_ptr_list_new(properties->value.nodes_val->count);

    json_node_ptr_list_t *properties_sorted = json_node_ptr_list_clone(properties->value.nodes_val);
    json_node_ptr_list_sort(properties_sorted, sort);

    for(unsigned int i = 0; i < properties->value.nodes_val->count; i++) {
        json_node_t *schema_node = json_node_ptr_list_at_index(properties_sorted, i);
        json_node_t *data = json_get_prop(json, schema_node->key); // todo: optimize
        if (data == NULL) {
            printf("Cannot find property: \"%s\".\n", schema_node->key);
            printf("Consider passing in \"null\" instead of removing the key from an object.\n");
            exit(1); // todo: error codes
        }
        json_node_t *out = parse_prop(schema_node, data);
        if (strcmp(json_get_prop(schema_node, "type")->value.string_val, "object") == 0) {
            for(unsigned int j = 0; j < out->value.nodes_val->count; j++) {
                json_node_t *out_prop = json_node_ptr_list_at_index(out->value.nodes_val, j);
                json_node_ptr_list_add(list, out_prop);
            }
            free(out);
        } else {
            sprintf((char*)num, "%i", list->count);
            out->key = strdup((char*)num);
            out->parent = ret;
            json_node_ptr_list_add(list, out);
        }
    }
    json_node_ptr_list_free(properties_sorted);
    ret->value.nodes_val = list;
    ret->type = JSON_ARRAY;
    return ret;
}

json_node_t *json_compress_node(json_node_t *json_node, json_node_t *schema_node, json_compress_options_t options) {
    (void)(options);
    json_node_t *ret = do_compression(json_node, schema_node);
    ret->parent = NULL;
    ret->key = strdup(json_node->key);
    return ret;
}

char *json_compress(char* json_buffer, char* json_schema, json_compress_options_t options) {
    (void)(options);
    json_node_t *root = json_parse(json_buffer);
    json_node_t *schema_root = json_parse(json_schema);
    json_node_t *compressed_node = json_compress_node(root, schema_root, options);
    char* compressed_json = json_stringify(compressed_node);
    json_free(root);
    json_free(schema_root);
    json_free(compressed_node);
    return compressed_json;
}

