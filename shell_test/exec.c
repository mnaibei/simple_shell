#include <stdio.h>
#include <unistd.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
	char *argv[2];

	argv[0] = "/bin/sh";
	argv[1] = NULL;
	execve(argv[0], argv, NULL);
	return (0);
}
