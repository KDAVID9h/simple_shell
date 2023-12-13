#include "shell.h"

/**
 * main - Entry point for the simple shell program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Description:
 * This function serves as the entry point for the simple shell program.
 * It initializes the shell and enters a loop to read and process user commands.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int main(int argc, char *argv[])
{
	char *buffer = NULL;
	ssize_t characters;
	char *expanded_command;  /* Déplacement de la déclaration ici */

	if (argc == 2)
	{
		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("fopen");
			return (EXIT_FAILURE);
		}

		while ((characters = custom_getline(&buffer)) != -1)
		{
			if (characters == 0)
				break;

			if (buffer[characters - 1] == '\n')
				buffer[characters - 1] = '\0';

			parse_command(buffer);
		}

		free(buffer);
		fclose(file);
	}
	else
	{
		/* Mode interactive */
		while (1)
		{
			printf("$$ ");
			characters = custom_getline(&buffer);

			if (characters == -1)
			{
				printf("\n");
				break;
			}

			if (characters == 0)
				continue;

			if (buffer[characters - 1] == '\n')
				buffer[characters - 1] = '\0';

			/* Utilisez la fonction expand_variables avant de traiter la commande */
			expanded_command = expand_variables(buffer);
			parse_command(expanded_command);
			free(expanded_command);
		}

		free(buffer);
	}

	return (0);
}
