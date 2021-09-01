#include "shell.h"

/**
 * main - main function of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *input = NULL, **tokens = NULL;
	int status = 0, ex = 0, tty = 1;
	size_t n = 0;
	pid_t child;

	tty = isatty(0);
	while (1)
	{
		child = fork();
		if (child == -1)
		{
			perror("");
			exit(errno);
		}
		if (child == 0)
		{
			if (isatty(0))
				write(1, "$ ", 3);
			getline(&input, &n, stdin);
			tokens = _getinput(input);
			free(input);
			tokens[0] = checkexec(tokens);
			if (execve(tokens[0], tokens, environ) == -1)
			{
				perror("");
				free(tokens);
				exit(errno);
			}
		}
		if (child > 0)
		{
			ex = WEXITSTATUS(status);
			wait(&status);
			free(input);
			if (tty == 0 || WEXITSTATUS(status) == 98)
				return (ex);
		}
	}
	return (0);
}

/**
 * _getinput - separes the imput in tokens
 *
 * @input: input
 * Return: pointer to array of strings
 */

char **_getinput(char *input)
{
	char **tokens;
	int a = 0, b, i, size = 0;
	char *buff;

	size = _check_tokens(input);
	tokens = malloc(sizeof(char *) * size);
	if (tokens == NULL)
	{
		perror("");
		exit(errno);
	}
	for (i = 0; i < size; i++)
		tokens[i] = NULL;
	buff = strtok(input, " \n");
	b = checkbin(input, tokens);
	if (b == 0)
	{
		exit(99);
		perror("");
	}
	if (b == 1)
	{
		exit(98);
		perror("");
	}
	while (buff != NULL)
	{
		b = _strlen(buff);
		tokens[a] = malloc(sizeof(char) * b + 1);
		_strcpy(tokens[a], buff);
		buff = NULL;
		buff = strtok(NULL, " \n");
		a++;
	}
	tokens[a] = NULL;
	return (tokens);
}

/**
 * checkexec - checks for an executable file
 *
 * @file: Name of the file to search
 * Return: directory of the file
 */

char *checkexec(char **file)
{
	char *buff = NULL, *buff2 = NULL, *buff3 = NULL, PATH[] = "PATH";
	int a = 0, b = 0, test = 0;
	struct stat st;

	if (stat(file[0], &st) == 0)
		return (file[0]);
	buff3 = _strcon("/", file[0]);
	for (a = 0; environ[a] != NULL; a++)
	{
		for (b = 0; environ[a][b] != '='; b++)
		{
		}
		buff = malloc(sizeof(char) * b + 1);
		for (b = 0; environ[a][b] != '='; b++)
			buff[b] = environ[a][b];
		buff[b] = '\0';
		if (_strcmp(buff, PATH) == 0)
		{
			free(buff);
			break;
		}
		free(buff);
	}
	buff = malloc(sizeof(char) * (_strlen(environ[a]) + 1));
	_strcpy(buff, environ[a]);
	strtok(buff, "=");
	buff2 = strtok(NULL, ":");
	while (buff2 != NULL)
	{
		buff2 = _strcon(buff2, buff3);
		test = stat(buff2, &st);
		if (test == 0)
		{
			free(file[0]), free(buff), free(buff3);
			return (buff2);
		}
		free(buff2);
		buff2 = strtok(NULL, ":");
	}
	free(file[0]), free(file), free(buff), free(buff3), exit(127);
}

/**
 * _check_tokens - check the ammount of tokens
 *
 * @input: input
 * Return: ammount of tokens
 */

int _check_tokens(char *input)
{
	char *buff2;
	int size = 0;

	buff2 = _strcon("", input);
	if (strtok(buff2, " \n") != NULL)
	{
		size++;
	}
	while (strtok(NULL, " \n") != NULL)
		size++;
	free(buff2);
	if (size == 0)
	{
		free(input);
		exit(97);
	}
	else
		size++;
	return (size);
}
