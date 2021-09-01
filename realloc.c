#include "shell.h"

/**
 * _realloc - adjust memory space allocated
 *
 * @tokens: tokens
 * Return: new array of strings
 */

char **_realloc(char **tokens)
{
	char **buff;
	int a = 0, size = 0, tsize = 0;

	while (tokens[a] != NULL)
	{
		tsize += _strlen(tokens[a]) + 1;
		a++;
	}
	buff = malloc(sizeof(char) * tsize);
	for (a = 0; tokens[a] != NULL; a++)
	{
		size = _strlen(tokens[a]) + 1;
		buff[a] = malloc(sizeof(char) * size);
		_strcpy(buff[a], tokens[a]);
	}
	free(tokens);
	return (buff);
}
