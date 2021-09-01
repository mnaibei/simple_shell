#include "shell.h"

/**
 * checkbin - checks if the input is a built in and executes it
 *
 * @input: input
 * @tokens: tokens
 * Return: 0 if succed, -1 if built in doesn´t exist
 */

int checkbin(char *input, char **tokens)
{
	int a, b;
	built_in bi[] = {
		{fenv, "env"},
		{fexit, "exit"},
		{NULL, NULL}
	};

	for (a = 0; bi[a].name != NULL; a++)
	{
		if (_strcmp(bi[a].name, input) == 0)
		{
			free(tokens), free(input);
			b = bi[a].func();
			return (b);
		}
	}
	return (-1);
}

/**
 * fenv - prints enviromental variables
 *
 * Return: 0
 */

int fenv(void)
{
	int a;
	size_t b = 0;

	for (a = 0; environ[a] != NULL; a++)
	{
		b = _strlen(environ[a]);
		write(1, environ[a], b + 1);
		write(1, "\n", 2);
	}
	return (0);
}

/**
 * fexit - exits the shell
 *
 * Return: 1
 */

int fexit(void)
{
	return (1);
}
