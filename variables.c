#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * expand_variables - Expand environment variables in a string.
 * @input: The input string with potential environment variables.
 *
 * This function expands environment variables (e.g., $HOME) in the input string.
 *
 * Return: A new dynamically allocated string with expanded variables.
 */
char *expand_variables(char *input)
{
	/* Copie la chaîne d'entrée pour éviter de la modifier directement */
	char *expanded = strdup(input);
	char *ptr = expanded;

	if (expanded == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	while (*ptr != '\0')
	{
		if (*ptr == '$')
		{
			/* Détecte le début d'une variable */
			char *variable_start = ptr + 1;
			/* Extraie le nom de la variable */
			char *end_ptr = variable_start;
			size_t variable_length = end_ptr - variable_start;
			/* Alloue de la mémoire pour la variable */
			char *variable = malloc(variable_length + 1);
			/* Récupère la valeur de la variable d'environnement */
			char *value = getenv(variable);

			while (*end_ptr != '\0' && !is_whitespace(*end_ptr))
			{
				end_ptr++;
			}

			if (variable == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}

			/* Copie le nom de la variable */
			strncpy(variable, variable_start, variable_length);
			variable[variable_length] = '\0';

			/* Trouve la fin de la variable */
			while (*ptr != '\0' && !is_whitespace(*ptr))
			{
				ptr++;
			}

			/* Si la variable d'environnement existe, remplace dans la chaîne */
			if (value != NULL)
			{
				size_t value_length = strlen(value);
				size_t remaining_length = strlen(ptr);
				size_t new_length = strlen(expanded) - variable_length + value_length;

				/* Alloue suffisamment d'espace pour la nouvelle chaîne */
				char *new_expanded = malloc(new_length + 1);
				if (new_expanded == NULL)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}

				/* Copie la partie de la chaîne avant la variable */
				strncpy(new_expanded, expanded, variable_start - expanded - 1);

				/* Copie la valeur de la variable d'environnement */
				strncpy(new_expanded + (variable_start - expanded - 1), value, value_length);

				/* Copie la partie de la chaîne après la variable */
				strncpy(new_expanded + (variable_start - expanded - 1) + value_length, ptr, remaining_length);

				/* Met fin à la nouvelle chaîne */
				new_expanded[new_length] = '\0';

				/* Libère la mémoire de la variable */
				free(variable);

				/* Libère l'ancienne chaîne et met à jour le pointeur */
				free(expanded);
				expanded = new_expanded;

				/* Réinitialise le pointeur pour qu'il pointe vers le début de la nouvelle chaîne */
				ptr = new_expanded + (variable_start - expanded - 1) + value_length - 1;
			}
			else
			{
				/* Si la variable d'environnement n'existe pas, libère la mémoire de la variable */
				free(variable);
			}
		}

		ptr++;
	}

	return (expanded);
}
