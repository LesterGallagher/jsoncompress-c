#ifndef __COMPRESS_H__
#define __COMPRESS_H__

typedef struct json_compress_options {
    char *example;
} json_compress_options_t;

char *json_compress(char* json_buffer, char* json_schema, json_compress_options_t options);

#endif