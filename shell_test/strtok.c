#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
        char *token, *buffer;
        size_t characters, bufsize = 20;
	unsigned int i;

        buffer = malloc(bufsize);

        printf("$ ");
        characters = getline(&buffer, &bufsize, stdin);

        if (buffer == NULL)
        {
                printf("error allocating buffer\n");
                exit(1);
        }

	token = strtok(buffer, " ");

	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}
        return (0);
}
