
#ifndef __XML_PARSER_HELPERS_H__
#define __XML_PARSER_HELPERS_H__

#include "xml-parser.h"

#define INDENTATION_SPACES 4

void xml_print_tree(xml_node_t *n);

void xml_free(xml_node_t *n);

xml_node_t *xml_parse_file(char *filename);

#endif
