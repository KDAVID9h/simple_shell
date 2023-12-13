#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse_command - Parse and process a command.
 * @command: The command to parse and process.
 *
 * This function parses the given command and executes the appropriate action,
 * either a built-in command or an external program.
 */
void parse_command(char *command)
{
	/* Fonction pour analyser la ligne de commande (séparation des commandes, gestion des opérateurs logiques, alias, variables, etc.) */
	char *token = strtok(command, " ");

	if (token == NULL)
	{
		printf("Null");
		return;
	}

	if (strcmp(token, "exit") == 0)
	{
		handle_exit();
	}
	else if (strcmp(token, "env") == 0)
	{
		handle_env();
	}
	else if (strcmp(token, "cd") == 0)
	{
		token = strtok(NULL, " ");
		handle_cd(token);
	}
	else if (strcmp(token, "setenv") == 0)
	{
		char *variable = strtok(NULL, " ");
		char *value = strtok(NULL, " ");
		handle_setenv(variable, value);
	}
	else if (strcmp(token, "unsetenv") == 0)
	{
		char *variable = strtok(NULL, " ");
		handle_unsetenv(variable);
	}
	else
	{
		execute_command(token);
	}
}

/* ... */

#define MAX_ARGS 64

/**
 * parse_arguments - Parse arguments from a command string.
 * @command: The command string to parse.
 *
 * This function splits the command string into an array of arguments.
 *
 * Return: An array of strings representing the arguments.
 */
char **parse_arguments(char *command)
{
	char **args = malloc(MAX_ARGS * sizeof(char *));
	int arg_count = 0;  /* Nombre d'arguments */
	int in_quote = 0;   /* Indique si nous sommes à l'intérieur de guillemets */
	char *token = strtok(command, " ");

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (token != NULL)
	{
		/* Alloue de la mémoire pour le nouvel argument */
		args[arg_count] = malloc(strlen(token) + 1);
		if (args[arg_count] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		/* Copie le token dans le nouvel argument */
		strcpy(args[arg_count], token);

		/* Vérifie si le token contient le début ou la fin d'une citation */
		if (token[0] == '"')
			in_quote = 1;

		if (token[strlen(token) - 1] == '"')
			in_quote = 0;

		/* Si nous sommes à l'intérieur de guillemets, concatène les tokens */
		if (in_quote)
		{
			/* Supprime les guillemets des extrémités du token */
			memmove(args[arg_count], args[arg_count] + 1, strlen(args[arg_count]));
			args[arg_count][strlen(args[arg_count]) - 1] = '\0';

			/* Lit le prochain token */
			token = strtok(NULL, "\"");
			if (token != NULL)
			{
				/* Alloue de la mémoire pour le nouvel argument */
				args[arg_count] = realloc(args[arg_count], strlen(args[arg_count]) + strlen(token) + 1);
				if (args[arg_count] == NULL)
				{
					perror("realloc");
					exit(EXIT_FAILURE);
				}

				/* Concatène le token */
				strcat(args[arg_count], token);
			}
		}

		arg_count++;

		/* Lit le prochain token */
		token = strtok(NULL, " ");
	}

	/* Ajoute un pointeur NULL à la fin du tableau d'arguments */
	args[arg_count] = NULL;

	return (args);
}

/**
 * handle_unsetenv - Handle the unsetenv built-in command.
 * @variable: The name of the environment variable to unset.
 *
 * This function removes an environment variable.
 */
void handle_unsetenv(char *variable)
{
	if (unsetenv(variable) != 0)
		perror("unsetenv");
}