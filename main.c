#include "shell.h"

/**
 * main - Entry point for the simple shell program.
 * @argc: The number of cmd-line arguments.
 * @argv: An array of strings containing the cmd-line arguments.
 *
 * Description:
 * This function serves as the entry point for the simple shell program.
 * It initialize the shell and enter a loop to read and process user cmds.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int main(int argc, char *argv[])
{
	char *buffer = NULL, *expanded_cmd; ssize_t characters;

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
			parse_cmd(buffer);
		}
		free(buffer); fclose(file);
	}
	else
	{
		while (1) /* Mode interactive */
		{
			printf("$ "); characters = custom_getline(&buffer);
			if (characters == -1)
			{
				break;
			}
			if (characters == 0)
				continue;
			if (buffer[characters - 1] == '\n')
				buffer[characters - 1] = '\0';
			expanded_cmd = expand_vars(buffer);/*fn expand_var.. avt*/
			parse_cmd(expanded_cmd); free(expanded_cmd);
		}
		free(buffer);
	}
	return (0);
}
