# JSON PARSER 2.0

## json_type Enum

- JSON_NUMBER
- JSON_NULL
- JSON_STRING 
- JSON_BOOL
- JSON_ARRAY 
- JSON_OBJECT

## struct json_node_t

Represents a node in a json tree. Can hold information on any json_type.

### json_type type

The json_type of the node.

### char* key

The key name of the node. Will be null if node is the root node of the json structure. It will be a string containing a number of the index in the array if the the node is an array item.

### json_node_t *parent

The parent node. Will be null if the node is the root node of the json structure.

## union json_value_t



## json_parse

```c
json_node_t *json_parse(char *json_buf);
```

Parses a json string and returns a json_node_t graph.

## json_stringify

```c
char *json_stringify(json_node_t *json_node);
```

Stringifies a json_node_t graph into a valid json string.

