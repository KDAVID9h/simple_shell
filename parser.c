#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse_cmd - Parse and process a cmd.
 * @cmd: The cmd to parse and process.
 *
 * This function parses the given cmd and executes the appropriate action,
 * either a built-in cmd or an external program.
 */
void parse_cmd(char *cmd)
{
	/*Fn pr analyser la ligne de cmde (séparation des cmdes...)*/
	char *tkn = strtok(cmd, " ");

	if (tkn == NULL)
	{
		printf("Null");
		return;
	}

	if (strcmp(tkn, "exit") == 0)
	{
		handle_exit();
	}
	else if (strcmp(tkn, "env") == 0)
	{
		handle_env();
	}
	else if (strcmp(tkn, "cd") == 0)
	{
		tkn = strtok(NULL, " ");
		handle_cd(tkn);
	}
	else if (strcmp(tkn, "setenv") == 0)
	{
		char *var = strtok(NULL, " ");
		char *value = strtok(NULL, " ");

		handle_setenv(var, value);
	}
	else if (strcmp(tkn, "unsetenv") == 0)
	{
		char *var = strtok(NULL, " ");

		handle_unsetenv(var);
	}
	else
	{
		execute_cmd(tkn);
	}
}

/* ... */

#define MAX_ARGS 64

/**
 * parse_arguments - Parse arguments from a cmd string.
 * @cmd: The cmd string to parse.
 *
 * This function splits the cmd string into an array of arguments.
 *
 * Return: An array of strings representing the arguments.
 */
char **parse_arguments(char *cmd)
{
	char **args = malloc(MAX_ARGS * sizeof(char *));
	int arg_cnt = 0;  /* Nombre d'arguments */
	int in_quote = 0;   /*Indique si nous sommes à l'intérieur de guillemets*/
	char *tkn = strtok(cmd, " ");

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (tkn != NULL)
	{
		/* Alloue de la mémoire pour le nouvel argument */
		args[arg_cnt] = malloc(strlen(tkn) + 1);
		if (args[arg_cnt] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strcpy(args[arg_cnt], tkn);/* Copie le tkn dans le nouvel arg*/
		if (tkn[0] == '"')/*ChekSiLetknContientLeDébutOuLaFinDUneCitation*/
			in_quote = 1;
		if (tkn[strlen(tkn) - 1] == '"')
			in_quote = 0;
		if (in_quote)/*Si nous sommes à l'intérieur ", concatène les tkns*/
		{
			memmove(args[arg_cnt], args[arg_cnt] + 1, strlen(args[arg_cnt]));
			args[arg_cnt][strlen(args[arg_cnt]) - 1] = '\0';
			tkn = strtok(NULL, "\"");/* Lit le prochain tkn */
			if (tkn != NULL)
			{
				/* Alloue de la mémoire pour le nouvel argument */
				args[arg_cnt] = realloc(args[arg_cnt], strlen(args[arg_cnt]) + strlen(tkn) + 1);
				if (args[arg_cnt] == NULL)
				{
					perror("realloc");
					exit(EXIT_FAILURE);
				}
				strcat(args[arg_cnt], tkn);/* Concatène le tkn */
			}
		}
		arg_cnt++;
		tkn = strtok(NULL, " ");/* Lit le prochain tkn */
	}
	args[arg_cnt] = NULL;/*Ajoute un pointeur NULL à la fin du tableau d'arg*/
	return (args);
}

/**
 * handle_unsetenv - Handle the unsetenv built-in cmd.
 * @var: The name of the environment var to unset.
 *
 * This function removes an environment var.
 */
void handle_unsetenv(char *var)
{
	if (unsetenv(var) != 0)
		perror("unsetenv");
}
