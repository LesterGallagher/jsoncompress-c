
#ifndef __XML_PARSER_H__
#define __XML_PARSER_H__

typedef enum xml_type { NODE, PCDATA, ATTR } xml_type;

union xml_val_t;

typedef struct xml_node {
    unsigned short children_len;
    union xml_val_t *children;
    struct xml_node_t *parent;
    xml_type type;
    char *name;
} xml_node_t;

typedef union xml_val {
    xml_node_t *node;
    char *pcdata;
    char *attr;
} xml_val_t;

xml_node_t *xml_parse(char* xml);

#endif
