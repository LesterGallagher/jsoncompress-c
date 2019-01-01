// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>
// #include "../CMemLeak.h"
// #include "../parse-json/helpers.h"
// #include "../parse-json/json-parser.h"
// #include "../lists/json-node-ptr-list.h"
// #include "json-decompress.h"
// #include "../hexdump.h"

// static const size_t json_node_size = sizeof(json_node_t);
// static const size_t json_value_size = sizeof(json_value_t);
// static char num[10];

// int sort(const void *a, const void *b) {
//     json_node_t *node1 = ((json_value_t*)a)->node_val;
//     json_node_t *node2 = ((json_value_t*)b)->node_val;
//     return strcmp(node1->key, node2->key);
// }

// json_node_t *do_decompression(json_node_t *json, json_node_t *schema);

// bool json_type_is_incompatible(char* type1, char* type2) {
//     return strcmp(type1, type2) != 0 && !((strcmp(type1, "integer") == 0 && strcmp(type2, "number") == 0)
//         || (strcmp(type1, "number") == 0 && strcmp(type2, "integer") == 0));
// }

// json_node_t *parse_prop(json_node_t *prop, json_node_t *val) {
//     (void)(prop);
//     (void)(val);
//     json_node_t *type_node = json_get_prop(prop, "type");
//     char* type = type_node->value->string_val;
//     if (json_type_is_incompatible(json_get_type_name(val->type), type)) {
//         printf("JSON Schema: \"%s\" incorrect type", prop->key);
//         getchar();
//         exit(1); // todo: error codes
//     } else if (strcmp(type, "array") == 0) {
//         json_node_t *arr = malloc(json_node_size); // todo: combine malloc calls
//         arr->val_len = val->val_len;
//         arr->value = malloc(json_value_size * val->val_len);
//         arr->type = JSON_ARRAY;
//         arr->key = NULL;
//         arr->parent = NULL;
//         json_node_t *schema_items = json_get_prop(prop, "items");
//         for(unsigned int i = 0; i < val->val_len; i++) {
//             arr->value[i].node_val = parse_prop(schema_items, val->value[i].node_val);
//             sprintf((char*)num, "%i", i);
//             arr->value[i].node_val->key = strdup((char*)num);
//             arr->value[i].node_val->parent = arr;
//         }
//         return arr;
//     } else if (strcmp(type, "object") == 0) {
//         return do_compression(val, prop);
//     } else { // STRING, NUMBER, BOOL, NULL
//         json_node_t *clone = malloc(json_node_size);
//         memcpy(clone, val, json_node_size);
//         clone->key = NULL;
//         clone->parent = NULL;
//         clone->val_len = val->val_len;
//         clone->value = malloc(json_value_size);
//         if (val->type == JSON_STRING) clone->value->string_val = strdup(val->value->string_val);
//         else memcpy(clone->value, val->value, json_value_size);
//         return clone;
//     }
// }

// json_node_t *do_decompression(json_node_t *json, json_node_t *schema) {
//     switch(json->type) {
//         case JSON_ARRAY:
        
//         break;
//         case JSON_OBJECT:

//         break;
//         default:

//         break;
//     }
// }

// json_node_t *json_decompress_node(json_node_t *json_node, json_node_t *schema_node, json_decompress_options_t options) {
    
// }

// char *json_decompress(char* json_buffer, char* json_schema, json_decompress_options_t options) {
//     (void)(options);
//     json_node_t *root = json_parse(json_buffer);
//     json_node_t *schema_root = json_parse(json_schema);
//     json_node_t *decompressed_node = 
//         root->type == JSON_ARRAY 
//         ? parse_prop(schema_root, root)
//         : root;
//     json_free(root);
//     json_free(schema_root);
//     return json_stringify(decompressed_node);
// }

