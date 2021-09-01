#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *buffer;
	size_t bufsize = 20;

	buffer = malloc(bufsize);

	printf("$ ");
	getline(&buffer, &bufsize, stdin);

	if (buffer == NULL)
	{
		printf("error allocating buffer\n");
		exit(1);
	}

	printf("%s", buffer);

	return (0);
}
