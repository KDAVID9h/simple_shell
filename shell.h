#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Déclarations des fonctions */
void execute_cmd(char *cmd);
void handle_exit(void);
void handle_env(void);
void handle_cd(char *dir);
void handle_setenv(char *var, char *value);
void handle_unsetenv(char *var);
void parse_cmd(char *cmd);
/* ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream); */
char *expand_vars(char *input);
char **parse_arguments(char *cmd);
#define BUFFER_SIZE 1024
ssize_t custom_getline(char **lineptr);
int is_whitespace(char c);

/*
//
int is_builtin(char *cmd);
int is_valid_cmd(char *cmd);
int is_valid_var(char *var);
int is_valid_var_value(char *var, char *value);
int is_valid_var_value_with_quotes(char *var, char *value);
int is_valid_var_value_with_quotes_and_spaces(char *var, char *value);
int is_valid_var_value_with_quotes_and_spaces_and_quotes(char *var, char *value);
int is_valid_var_value_with_quotes_and_spaces_and_quotes_and_spaces(char *var, char *value);
int is_valid_var_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces(char *var, char *value);
int is_valid_var_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces(char *var, char *value);
int is_valid_var_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces_and_spaces(char *var, char *value);
int is_valid_var_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces(char *var, char *value);
int is_valid_var_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces(char *var, char *value);

int is_valid_var_value_with_quotes_and_spaces_and_quotes_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces_and_spaces(char *var, char *value);
/*/


#endif /* SHELL_H */
