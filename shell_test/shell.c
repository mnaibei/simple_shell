#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int mypid(void);
char* input(void);
/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
	char *argv[] = {"", NULL};
	char *buffer, *exit = "exit";
	int len;

	while (buffer != exit)
	{
		if (fork() == 0)
		{
			buffer = input();
			len = strlen(buffer);
			buffer[len - 1] = 0;
			argv[0] = buffer;

			if (execve(argv[0], argv, NULL) == -1)
			{
				printf("Error: command not found\n");
			}
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}

char* input(void)
{
        char *buffer;
        size_t bufsize = 20;

        buffer = malloc(bufsize * sizeof(char));
	if (buffer == NULL)
        {
                printf("error allocating buffer\n");
                exit(1);
        }

        printf("$ ");
        getline(&buffer, &bufsize, stdin);

        return (buffer);
}

/**
 * main - PID
 * aaa
 * Return: Always 0.
 */
int mypid(void)
{
	pid_t my_pid;

	my_pid = getpid();
	return (my_pid);
}
