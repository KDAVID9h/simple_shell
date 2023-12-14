#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * execute_cmd - Execute a cmd in a child process.
 * @cmd: The cmd to execute.
 *
 * This function forks a child process & uses execvp to execute given cmd.
 * The parent process waits for the child to complete.
 */
void execute_cmd(char *cmd)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		/* Child process */
		char **args = parse_arguments(cmd);

		if (args[0] != NULL)
		{
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(stderr, "cmd not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, NULL, 0);
	}
}

/**
 * handle_exit - Handle the exit built-in cmd.
 *
 * This function prints a farewell message and exits the shell.
 */
void handle_exit(void)
{
	printf("Exiting the shell.\n");
	exit(EXIT_SUCCESS);
}

/**
 * handle_env - Handle the env built-in cmd.
 *
 * This function prints the current environment vars.
 */
void handle_env(void)
{
	extern char **environ;
	char **env = environ;  /* Déclaration en dehors de la boucle */

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * handle_cd - Handle the cd built-in cmd.
 * @dir: The directory to change to. If NULL, change to the home directory.
 *
 * This function changes the current working directory.
 * If no argument is provided, it changes to the home directory.
 */
void handle_cd(char *dir)
{
	if (dir == NULL)
		dir = getenv("HOME");

	if (chdir(dir) != 0)
		perror("chdir");
}

/**
 * handle_setenv - Handle the setenv built-in cmd.
 * @var: The name of the environment var.
 * @value: The value to set for the environment var.
 *
 * This function sets or initializes an environment var.
 */
void handle_setenv(char *var, char *value)
{
	if (setenv(var, value, 1) != 0)
		perror("setenv");
}
