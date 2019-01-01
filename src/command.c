#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "CMemLeak.h"
#include "command.h"

program_t *program_new(char* version, char* description, char* usage) {
    program_t *program = (program_t*)malloc(sizeof(program_t));
    program->version = version;
    program->description = description;
    program->usage = usage;
    program->commands = program_command_ptr_list_new(2);
    program->options = program_option_ptr_list_new(2);
    return program;
}

void program_commands_add(program_t *program, char* name, char* description, char* usage) {
    program_command_t *com = (program_command_t*)malloc(sizeof(program_command_t));
    com->name = name;
    com->description = description;
    com->usage = usage;
    com->active = false;
    com->options = program_option_ptr_list_new(2);
    program->commands[program] = com;
}

program_command_t *program_commands_get_ptr(program_t *program, char* name) {
    for(int i = 0; i < program->commands_len; i++) {
       if (strcmp(name, program->commands[i].name) == 0) {
            return program->commands + i * sizeof(program_command_t*);
        }
    }
    fprintf(stderr, "No program command with the name: \"%s\" was found.\n", name);
    exit(1);
}

program_command_t program_commands_get(program_t *program, char* name) {
    program_command_t *cmd = program_commands_get_ptr(program, name);
    return *cmd;
}

program_command_t *program_commands_get_active_ptr(program_t *program) {
    for(int i = 0; i < program->commands_len; i++) {
       if (program->commands[i].active) return program->commands + i * sizeof(program_command_t*);
    }
    fprintf(stderr, "No active program command was found.\n");
    exit(1);
}

program_command_t program_commands_get_active(program_t *program) {
    program_command_t *active = program_commands_get_active_ptr();
    return *active;
}

bool program_commands_get_active_exists(program_t *program) {
    return program_commands_get_active_ptr(program) != NULL;
}

void program_option_add(program_t *program, char *short_option, char *long_option, char *description, int args_len) {
    program_option_t option = {
        .short_option = short_option,
        .long_option = long_option,
        .description = description,
        .args_len = args_len,
        .args = (char**)calloc(args_len, sizeof(char*)),
        .is_set = false
    };
    program->options[program.options_len++] = option;
}

program_option_t *program_option_get_ptr(program_t *program, char *option) {
    for(int i = 0; i < program->options_len; i++) {
       if (strcmp(option, program->options[i].short_option) == 0 
            || strcmp(option, program->options[i].long_option) == 0) {
            return program->options + i * sizeof(program_option_t);
        }
    }
    fprintf(stderr, "No program option with the name: \"%s\" was found.\n", option);
    exit(1);
}

program_option_t program_option_get(program_t *program, char *option) {
    program_option_t *opt = program_option_get_ptr(program, option);
    return *opt;
}

void program_commands_options_add(program_t *program, char* command_name, char *short_option, char *long_option, char *description, int args_len) {
    program_command_t *cmd = program_commands_get_ptr(command_name);
    program_option_t option = {
        .short_option = short_option,
        .long_option = long_option,
        .description = description,
        .args_len = args_len,
        .args = (char**)calloc(args_len, sizeof(char*)),
        .is_set = false
    };
    cmd->options[cmd->options_len++] = option;
}

program_option_t program_commands_options_get(program_t *program, char *option) {
    for(int i = 0; i < program->options_len; i++) {
       if (strcmp(option, program->options[i].short_option) == 0 
            || strcmp(option, program->options[i].long_option) == 0) {
            return program->options[i];
        }
    }
    fprintf(stderr, "No program option with the name: \"%s\" was found.\n", option);
    exit(1);
}

void program_print_help(program_t *program, int argc, char** argv) {
    (void)(argc);
    char* usage = program.name == NULL ? argv[0] : program.name;
    if (program.usage == NULL) {
        if (program.options_len != 0) {
            strcat(usage, " [options]");
        }
    } else {
        strcat(usage, " ");
        strcat(usage, program.usage);
    }
    printf("Usage: %s\n", usage);
    if (program.description != NULL) {
        printf("\n%s\n", program.description);
    }
    if (program.options_len > 0) {
        int longest_str_len = 0;
        puts("\nOptions:");
        for(int i = 0; i < program.options_len; i++) {
            int len = strlen(program.options[i].short_option) + strlen(program.options[i].long_option);
            if (len > longest_str_len) longest_str_len = len;
        }
        longest_str_len++;
        for(int i = 0; i < program.options_len; i++) {
            int len = strlen(program.options[i].short_option) + strlen(program.options[i].long_option);
            int padding = longest_str_len - len;
            printf("  %s,  %s, %*c%s\n", program.options[i].short_option, program.options[i].long_option, padding, ' ', program.options[i].description);
        }
    }
    if (program.commands_len > 0) {
        int longest_str_len = 0;
        puts("\nCommands:");
        for(int i = 0; i < program.commands_len; i++) {
            int len = strlen(program.commands[i].name);
            if (len > longest_str_len) longest_str_len = len;
        }
        longest_str_len++;
        for(int i = 0; i < program.commands_len; i++) {
            int len = strlen(program.commands[i].name);
            int padding = longest_str_len - len;
            printf("  %s   %*c%s\n", program.commands[i].name, padding, ' ', program.options[i].description);
        }
    }
    exit(0);
}

void program_parse(int argc, char** argv) {
    if (argc >= 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        program_print_help(argc, argv);
        exit(0);
    }

    for(int i = 1; i < argc; i++) {
        for(int j = 0; j < program.options_len; j++) {
            if (strcmp(argv[i], program.options[j].short_option) == 0 
                || strcmp(argv[i], program.options[j].long_option) == 0) {
                program.options[j].is_set = true;
                int k = 0;
                while(k < program.options[j].args_len && (i + k + 1) < argc) {
                    program.options[j].args[k] = argv[i+k+1];
                    k++;
                }
            }
        }
    }

    for(int i = 1; i < argc; i++) {
        for(int j = 0; j < program.commands_len; j++) {
            if (strcmp(argv[i], program.commands[j].name) == 0) {
                program.commands[j].active = true;
            }
        }
    }
}
