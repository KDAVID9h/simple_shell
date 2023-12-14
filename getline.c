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
	size_t bufsize = BUFFER_SIZE; /* Taille initiale du tampon */
	size_t i = 0;

	static char buffer[BUFFER_SIZE]; /*Tampon pr min les appels au sys read*/

	*lineptr = malloc(bufsize); /* Initialiser le pointeur de la ligne */

	if (*lineptr == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (1) /* Boucle de lecture */
	{
		int c = getchar(); /* Lire un caractère supplémentaire du terminal */

		if (i == bufsize) /* Vérifier si le tampon statique est épuisé */
		{
			bufsize += BUFFER_SIZE;
			*lineptr = realloc(*lineptr, bufsize);

			if (*lineptr == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		(*lineptr)[i] = buffer[i]; /* Lire un caractère du tampon statique */
		if ((*lineptr)[i] == '\n' || (*lineptr)[i] == EOF) /*fin Ln ou de file*/
		{
			(*lineptr)[i] = '\0';
			return (i);
		}
		i++;
		if (c == EOF) /* Vérifier la fin de fichier */
		{
			return (-1);
		}
		buffer[i - 1] = c; /* Stocker le caractère dans le tampon statique */
	}
}
