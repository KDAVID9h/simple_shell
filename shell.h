#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Déclarations des fonctions */
void execute_command(char *command);
void handle_exit(void);
void handle_env(void);
void handle_cd(char *dir);
void handle_setenv(char *variable, char *value);
void handle_unsetenv(char *variable);
void parse_command(char *command);
/* ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream); */
char *expand_variables(char *input);
char **parse_arguments(char *command);
#define BUFFER_SIZE 1024
ssize_t custom_getline(char **lineptr);
int is_whitespace(char c);

/*
//
int is_builtin(char *command);
int is_valid_command(char *command);
int is_valid_variable(char *variable);
int is_valid_variable_value(char *variable, char *value);
int is_valid_variable_value_with_quotes(char *variable, char *value);
int is_valid_variable_value_with_quotes_and_spaces(char *variable, char *value);
int is_valid_variable_value_with_quotes_and_spaces_and_quotes(char *variable, char *value);
int is_valid_variable_value_with_quotes_and_spaces_and_quotes_and_spaces(char *variable, char *value);
int is_valid_variable_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces(char *variable, char *value);
int is_valid_variable_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces(char *variable, char *value);
int is_valid_variable_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces_and_spaces(char *variable, char *value);
int is_valid_variable_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces(char *variable, char *value);
int is_valid_variable_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces(char *variable, char *value);

int is_valid_variable_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces(char *variable, char *value);
/*/


#endif /* SHELL_H */
