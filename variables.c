#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * expand_vars - Expand environment vars in a string.
 * @input: The input string with potential environment vars.
 *
 * This function expands environment vars (e.g., $HOME) in the input string.
 *
 * Return: A new dynamically allocated string with expanded vars.
 */
char *expand_vars(char *input)
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
			char *var_start = ptr + 1;/*Détecte le début d'une var */
			char *end_ptr = var_start;/*Extraie le nom de la var */
			size_t var_length = end_ptr - var_start;
			char *var = malloc(var_length + 1);/*mémoire pr la var*/
			char *value = getenv(var);/*RécupèreLaValeurDeLaVar d'env*/

			while (*end_ptr != '\0' && !is_whitespace(*end_ptr))
			{
				end_ptr++;
			}
			if (var == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			strncpy(var, var_start, var_length);/*CopieNomDeVar*/
			var[var_length] = '\0';
			while (*ptr != '\0' && !is_whitespace(*ptr))/*TrouveLaFin du var*/
			{
				ptr++;
			}
			if (value != NULL)/*Si la var d'env existe,remplace ds la chaîne*/
			{
				size_t value_length = strlen(value);
				size_t remaining_length = strlen(ptr);
				size_t new_length = strlen(expanded) - var_length + value_length;
				char *new_expanded = malloc(new_length + 1);/*EspPrLaNvlChaîn*/

				if (new_expanded == NULL)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}
				/* Copie la partie de la chaîne avant la var */
				strncpy(new_expanded, expanded, var_start - expanded - 1);
				/* Copie la valeur de la var d'environnement */
				strncpy(new_expanded + (var_start - expanded - 1), value, value_length);
				/* Copie la partie de la chaîne après la var */
				strncpy(new_expanded + (var_start - expanded - 1) + value_length, ptr, remaining_length);
				new_expanded[new_length] = '\0';/*Met fin à la nvlle chaîne*/
				free(var);/* Libère la mémoire de la var */
				free(expanded);/*LibèreL'AncienneChaîneEtMet à jr le pointeur*/
				expanded = new_expanded;
				/*RéinitialiseLePointeurPrQ'ilPointeVersLeDébutDeLaNvlChaîne*/
				ptr = new_expanded + (var_start - expanded - 1) + value_length - 1;
			}
			else
			{
				free(var);/*SiLaVarD'envN'existePas,libèreLaMémoireDeLaVar*/
			}
		}
		ptr++;
	}
	return (expanded);
}
