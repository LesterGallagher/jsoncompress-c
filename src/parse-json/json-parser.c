#include "json-parser.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "../CMemLeak.h"
#include "stringbuilder.h"
#include <math.h>

typedef enum { WAITFORKEY, BEFOREVALUEWRITE, AFTERVALUEWRITE } writing_state;
typedef enum { WM_INITIAL, WM_JSON_OBJECT, WM_JSON_ARRAY } writing_mode;
 
void *parse_err(const char *fmt, char s, unsigned short i) {
    s != '\0' ? fprintf(stderr, fmt, s, i) : fprintf(stderr, fmt);
    return NULL;
}

char *substring(const char *str, size_t begin, size_t len) {
    char *subbuff = malloc(len + 1);
    memcpy(subbuff, &str[begin], len);
    subbuff[len] = '\0';
    return subbuff;
}

unsigned short str_slice_eq(const char *str, size_t begin, size_t len, const char *target) {
    char* sub = substring(str, begin, len);
    int r = strcmp(sub, target);
    free(sub);
    return r == 0;
}

void init_node_value(json_node_t *json_node) {
    switch(json_node->type) {
        case JSON_ARRAY:
        case JSON_OBJECT:
        json_node->value.nodes_val = json_node_ptr_list_new(8);
        break;

        // // todo: The following case statements don't require initializations. You might as well remove them.
        // case JSON_BOOL:
        // json_node->value.bool_val = false;
        // break;
        // case JSON_NULL:
        // // value is not set
        // memcpy(json_node, "\0\0\0\0\0\0\0\0\0\0\0", sizeof(json_value_t)); // todo: the user should not access this field. So it doesn't really have to be set to a bunch of nulls but we'll do it anyway.
        // break;  
        // case JSON_NUMBER:
        // json_node->value.num_val = 0;
        // break;
        // case JSON_STRING:
        // json_node->value.string_val = NULL;
        // break;
    }
}

json_node_t *create_key_value_node(json_type type, writing_mode mode, char *key, json_node_t *curr) {
    json_node_t *new_node = malloc(sizeof(json_node_t));
    new_node->type = type;
    if (mode == WM_JSON_ARRAY) sprintf(key, "%u", curr->value.nodes_val->count);
    new_node->key = malloc(strlen(key) + 1);
    strcpy(new_node->key, key);
    new_node->parent = curr;
    init_node_value(new_node);
    return new_node;
}

json_node_t *json_parse(char *json_buf) {
    unsigned int len = strlen(json_buf);
    json_node_t *curr = NULL;
    writing_state ws = BEFOREVALUEWRITE;
    writing_mode mode = WM_INITIAL;
    char s;
    unsigned short key_write_index;
    char key[MAX_KEY_SIZE] = "";

    for (unsigned int i = 0; i < len; i++) {
        s = json_buf[i];
        switch (ws) {
        case AFTERVALUEWRITE:
            if (s == ',') ws = mode == WM_JSON_ARRAY ? BEFOREVALUEWRITE : WAITFORKEY;
            else if (s == '}' || s == ']') {
                if (mode == WM_JSON_ARRAY && s == '}') return parse_err("syntax error character '%c'(#%i): expected ']'", s, i);
                else if (mode == WM_JSON_OBJECT && s == ']') return parse_err("syntax error character '%c'(#%i): expected '}'", s, i);
                else if (curr->parent != NULL) { // close child
                    ws = AFTERVALUEWRITE;
                    // todo: trim json_node_ptr_list children
                    curr = curr->parent;
                    mode = curr->type == JSON_ARRAY ? WM_JSON_ARRAY : WM_JSON_OBJECT;
                } else return curr; // we are done, and back at the root node
            }
            break;
        case BEFOREVALUEWRITE:
            if (isspace(s)) continue;
            if (s == '"') {
                s = json_buf[++i];
                unsigned int start = i;
                while (json_buf[i] != '"' || (i && json_buf[i - 1] == '\\'))
                    if (++i >= len) return parse_err("Syntax error: Unexpected end of string, expected a character in a string value", '\0', 0);
                s = json_buf[i];
                char *val = substring(json_buf, start, i - start);
                json_node_t *str_node = create_key_value_node(JSON_STRING, mode, key, curr);
                str_node->value.string_val = val;
                if(curr != NULL) json_node_ptr_list_add(curr->value.nodes_val, str_node);
                else curr = str_node;
                ws = AFTERVALUEWRITE;
            }
            else if (isdigit(s) || s == '.' || s == '-') {
                unsigned int start = i;
                while (isdigit(s) || s == '.') { // TODO: error check while loops
                    if (++i >= len) return parse_err("Syntax error: Unexpected end of string, expected a character inside a number value", '\0', 0);
                    else s = json_buf[i];
                }
                char *strval = substring(json_buf, start, --i - start + 1);
                json_node_t *num_node = create_key_value_node(JSON_NUMBER, mode, key, curr);
                num_node->value.num_val = strtod(strval, NULL);
                free(strval);
                if (curr != NULL) json_node_ptr_list_add(curr->value.nodes_val, num_node);
                else curr = num_node;
                ws = AFTERVALUEWRITE;
            }
            else if ((i + 4) <= len && str_slice_eq(json_buf, i, 4, "true")) {
                json_node_t *bool_node = create_key_value_node(JSON_BOOL, mode, key, curr);
                bool_node->value.bool_val = true;
                i = i + 3;
                if (curr != NULL) json_node_ptr_list_add(curr->value.nodes_val, bool_node);
                else curr = bool_node;
                ws = AFTERVALUEWRITE;
            }
            else if ((i + 5) <= len && str_slice_eq(json_buf, i, 5, "false")) {
                json_node_t *bool_node = create_key_value_node(JSON_BOOL, mode, key, curr);
                bool_node->value.bool_val = 0;
                i = i + 4;
                if (curr != NULL) json_node_ptr_list_add(curr->value.nodes_val, bool_node);
                else curr = bool_node;
                ws = AFTERVALUEWRITE;
            } else if ((i + 4) <= len && str_slice_eq(json_buf, i, 4, "null")) { // value is null
                json_node_t *null_node = create_key_value_node(JSON_NULL, mode, key, curr);
                // memcpy(&null_node->value, "\0\0\0\0\0\0\0\0\0\0\0", sizeof(json_value_t)); // todo: the user should not access this field. So it doesn't really have to be set to a bunch of nulls but we'll do it anyway.
                i = i + 3;
                if (curr != NULL) json_node_ptr_list_add(curr->value.nodes_val, null_node);
                else curr = null_node;
                ws = AFTERVALUEWRITE;
            } else if (s == '{') {
                json_node_t *new_obj_node = create_key_value_node(JSON_OBJECT, mode, key, curr);
                if (curr != NULL) json_node_ptr_list_add(curr->value.nodes_val, new_obj_node);
                curr = new_obj_node;
                mode = WM_JSON_OBJECT;
                ws = WAITFORKEY;
            } else if (s == '[') {
                json_node_t *new_arr_node = create_key_value_node(JSON_ARRAY, mode, key, curr);
                if (curr != NULL) json_node_ptr_list_add(curr->value.nodes_val, new_arr_node);
                curr = new_arr_node;
                mode = WM_JSON_ARRAY;
                ws = BEFOREVALUEWRITE;
            } else return parse_err("Syntax error: Unexpected character '%c'(#%i). expected a value", s, i);
            break;
        case WAITFORKEY:
            if (isspace(s)) continue;
            if (s == '}') {
                ws = AFTERVALUEWRITE;
                i--;
                continue;
            }
            if (s != '"') {
                return parse_err("Syntax error: Unexpected character '%c'(#%i). expected a '\"' character", s, i);
            }
            key_write_index = 0;
            i++;
            while (1) {
                if (i >= len) return parse_err("Syntax error: Unexpected end of string, expected a key character", '\0', 0);
                if (json_buf[i] == '"' && json_buf[i - 1] != '\\')  break;  // done writing title string
                else key[key_write_index++] = json_buf[i++];
            }
            key[key_write_index] = '\0';
            while (1) {
                if (i >= len) return parse_err("Syntax error: Unexpected end of string, expected a ':' character", '\0', 0);
                if (isspace(json_buf[++i])) continue;
                if (json_buf[i] == ':') break;
                else return parse_err("Syntax error: Unexpected character '%c'(#%i). expected a ':' character", s, i);
            }
            ws = BEFOREVALUEWRITE;
            break;
        }
    }
    if (curr != NULL && curr->parent == NULL) return curr; // todo: this json string holds a single value
    return parse_err("syntax error", '\0', 0);
}

void json_stringify_rec(json_node_t *json_node, stringbuilder_t *stringbuilder) {
    char* buf[32];
    double num;

    switch(json_node->type) {
        case JSON_ARRAY:
        stringbuilder_add(stringbuilder, '[');
        for(unsigned int i = 0; i < json_node->value.nodes_val->count; i++) {
            json_node_t *child = json_node_ptr_list_at_index(json_node->value.nodes_val, i);
            json_stringify_rec(child, stringbuilder);
            if (i < json_node->value.nodes_val->count - 1) stringbuilder_add(stringbuilder, ',');
        }
        stringbuilder_add(stringbuilder, ']');
        break;
        case JSON_OBJECT:
        stringbuilder_add(stringbuilder, '{');
        for(unsigned int i = 0; i < json_node->value.nodes_val->count; i++) {
            stringbuilder_concat(stringbuilder, json_node->key, strlen(json_node->key));
            stringbuilder_add(stringbuilder, ':');
            json_node_t *child = json_node_ptr_list_at_index(json_node->value.nodes_val, i);
            json_stringify_rec(child, stringbuilder);
            if (i < json_node->value.nodes_val->count - 1) stringbuilder_add(stringbuilder, ',');
        }
        stringbuilder_add(stringbuilder, '}');
        break;
        case JSON_STRING:
        stringbuilder_add(stringbuilder, '"');
        stringbuilder_concat(stringbuilder, json_node->value.string_val, strlen(json_node->value.string_val));
        stringbuilder_add(stringbuilder, '"');
        break;
        case JSON_BOOL:
        stringbuilder_concat(
            stringbuilder, 
            json_node->value.bool_val ? "true" : "false",
            json_node->value.bool_val ? 4 : 5);
        break;
        case JSON_NULL:
        stringbuilder_concat(stringbuilder, "null", 4);
        break;
        case JSON_NUMBER:
        num = json_node->value.num_val;
        sprintf((char*)buf, "%g", num);
        stringbuilder_concat(stringbuilder, (char*)buf, strlen((char*)buf));
        break;
    }
}

char *json_stringify(json_node_t *json_node) {
    stringbuilder_t stringbuilder = {
        .array = (char*)malloc(sizeof(char) * 1024),
        .allocated = 1024,
        .length = 0,
    };
    json_stringify_rec(json_node, &stringbuilder);
    char* ret = stringbuilder.array;
    return ret;
}

