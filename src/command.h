#ifndef __program_H__
#define __program_H__

#include <stdbool.h>
#include "lists/program-command-ptr-list.h"
#include "lists/program-option-ptr-list.h"

#ifndef PROGRAM_ARR_MAX_LEN
#define PROGRAM_ARR_MAX_LEN 100
#endif

typedef struct program_option {
    char *short_option;
    char *long_option;
    char *description;
    bool is_set;
    int args_len;
    char **args;
} program_option_t;

struct program_command;
typedef void program_command_cb(struct program_command*);

typedef struct program_command {
    char *name;
    char *description;
    char *usage;
    program_option_ptr_list_t *options;
    program_command_ptr_list_t *commands;
    bool active;
} program_command_t;

typedef struct program {
    char *name;
    char *version;
    char *description;
    char *usage;
    program_option_ptr_list_t *options;
    program_command_ptr_list_t *commands;
} program_t;

void program_commands_add(char* name, char* description, char* usage);

program_command_t *program_commands_get_ptr(char* name);

program_command_t program_commands_get(char* name);

program_command_t *program_commands_get_active_ptr();

program_command_t program_commands_get_active();

bool program_commands_get_active_exists();

void program_commands_options_add(char* command_name, char *short_option, char *long_option, char *description, int args_len);

void program_option_add(char *short_option, char *long_option, char *description, int args_len);

program_option_t program_option_get(char *option);

void program_print_help(int argc, char** argv);

void program_parse(int argc, char** argv);

#endif
