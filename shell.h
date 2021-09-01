#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

extern char **environ;
int _check_tokens(char *input);
char **_getinput(char *input);
char *_strcpy(char *dest, const char *src);
char *_strcon(char *dest, char *src);
int _strcmp(char *src1, char *src2);
int _strlen(char *str);
char *checkexec(char **file);
int checkbin(char *input, char **tokens);
int fexit(void);
int fenv(void);

/**
 * struct builtin - built in of the shell
 *
 * @func: function
 * @name: name of the built in
 */

typedef struct builtin
{
	int (*func)();
	char *name;
} built_in;

#endif /* SHELL_H */
