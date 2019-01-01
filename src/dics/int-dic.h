#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef __INT_LIST_H__
#define __INT_LIST_H__

typedef struct int_dic_kvp {
    char* key;
    bool in_use;
    int value;
} int_dic_kvp_t;

typedef struct int_dic {
    unsigned int table_size;
    unsigned int size;
    int_dic_kvp_t *data;
} int_dic_t;

typedef void int_dic_iterate_cb(int);

#define MAP_MISSING -3
#define MAP_FULL -2
#define MAP_OMEM -1
#define MAP_OK 0

int_dic_t *int_dic_new(unsigned int initialSize);

void int_dic_put(int_dic_t *m, char* key, int value);

int *int_dic_get(int_dic_t *m, char* key);

void int_dic_iterate(int_dic_t *m, int_dic_iterate_cb *f);

bool int_dic_remove(int_dic_t *m, char* key);

void int_dic_free(int_dic_t *m);

#endif

