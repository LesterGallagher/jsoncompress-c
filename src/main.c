#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "CMemLeak.h"
#include "json-compress/json-compress.h"
#include "json-compress/json-decompress.h"
#include "parse-json/json-parser.h"
#include "parse-json/helpers.h"

#define _(STRING) gettext(STRING)

#define DEFAULT_BUF_SIZE 512

char* read_file(char *filename) {
    char *str = NULL;
    long length;
    FILE *f = fopen(filename, "rb");
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END)) return NULL;
    length = ftell(f);
    if (fseek(f, 0, SEEK_SET)) return NULL;
    str = malloc(length + sizeof(char));
    if (str) fread(str, 1, length, f);
    else return NULL;
    str[length] = '\0';
    if (fclose(f)) return NULL;
    return str;
}

int main(int argc, char** argv)
{
    puts("PROGRAM: START");
    (void)(argc);
    (void)(argv);

    char *json = read_file("test/testjson.json");
    char *schema = read_file("test/testschema.json");

    json_compress_options_t opts;

    char* compressed = json_compress(json, schema, opts);

    puts(compressed);

    free(json);
    free(schema);
    free(compressed);

    setlocale(LC_ALL, "");
    bindtextdomain("main", "usr/share/locale");
    textdomain("main");
    printf(_("Hello, world!\n"));

    puts("PROGRAM: FINISH");
    return 0;
}
