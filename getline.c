#include "shell.h"

/**
 * custom_getline - Read a line from the standard input.
 * @lineptr: A pointer to the buffer storing the line.
 *
 * This function reads a line from the standard input and adjusts the
 * buffer size accordingly. It uses a static buffer to minimize the number
 * of calls to the read system call.
 *
 * Return: The number of characters read, or -1 on failure or end-of-file.
 */
ssize_t custom_getline(char **lineptr)
{
	/* Taille initiale du tampon */
	size_t bufsize = BUFFER_SIZE;

		size_t i = 0;

	/* Tampon statique pour minimiser les appels au système read */
	static char buffer[BUFFER_SIZE];

	/* Initialiser le pointeur de la ligne */
	*lineptr = malloc(bufsize);

	if (*lineptr == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	/* Boucle de lecture */
	while (1)
	{
		/* Lire un caractère supplémentaire du terminal */
		int c = getchar();

		/* Vérifier si le tampon statique est épuisé */
		if (i == bufsize)
		{
			bufsize += BUFFER_SIZE;
			*lineptr = realloc(*lineptr, bufsize);

			if (*lineptr == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		/* Lire un caractère du tampon statique */
		(*lineptr)[i] = buffer[i];

		/* Vérifier la fin de la ligne ou de fichier*/
		if ((*lineptr)[i] == '\n' || (*lineptr)[i] == EOF)
		{
			(*lineptr)[i] = '\0';
			return (i);
		}

		i++;

		/* Vérifier la fin de fichier */
		if (c == EOF)
		{
			return (-1);
		}

		/* Stocker le caractère dans le tampon statique */
		buffer[i - 1] = c;
	}
}
