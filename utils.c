#include "shell.h"
#include <ctype.h>

/* Fn utilitaires qui peuvent être utilisées dans != parties du programme */
/**
 * is_whitespace - Check if a character is whitespace.
 * @c: The character to check.
 *
 * Description:
 * This function determines whether the given character is a whitespace
 * character, including space, tab, and newline.
 *
 * Return: 1 if the character is whitespace, 0 otherwise.
 */
int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
