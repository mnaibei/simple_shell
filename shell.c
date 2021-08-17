#include "test.h"

/*
  *Function Declarations for builtin shell commands:
 */
int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);

/*
  *List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &sh_cd,
    &sh_help,
    &sh_exit
};
int lsh_num_builtins(void)
{
    return (sizeof(builtin_str) / sizeof(char *));
}
/*
  *Builtin function implementations.
*/

/*
  * @brief Bultin command: change directory.
   *@param args List of args.  args[0] is "cd".  args[1] is the directory.
   *@return Always returns 1, to continue executing.
 */
int sh_cd(char **args)
{
    if (args[1] == NULL)
    {
    fprintf(stderr, "sh: expected argument to \"cd\"\n");
  } else
  {
    if (chdir(args[1]) != 0)
    {
        perror("sh");
    }
    }
    return (1);
    }

/*
  * @brief Builtin command: print help.
   *@param args List of args.  Not examined.
   *@return Always returns 1, to continue executing.
 */
int sh_help(char **args)
{
    int i;
  
    printf("Mucha and Moreen Simple Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++)
    {
    printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return (1);
}

/*
  * @brief Builtin command: exit.
   *@param args List of args.  Not examined.
   *@return Always returns 0, to terminate execution.
 */
int sh_exit(char **args)
{
    return (0);
}

/*
  *@brief Launch a program and wait for it to terminate.
  *@param args Null terminated list of arguments (including program).
  *@return Always returns 1, to continue execution.
 */
int sh_launch(char **args)
{
    pid_t pid, wpid;
    int status;
    pid = fork();
    
    if (pid == 0)
    {
    /* Child process*/
    if (execvp(args[0], args) == -1)
    {
      perror("sh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0)
  {
    /* Error forking*/
    perror("sh");
  } else{
    /*Parent process*/
    do
    {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

  return (1);
  }

/*
  * @brief Execute shell built-in or launch program.
   *@param args Null terminated list of arguments.
   *@return 1 if the shell should continue running, 0 if it should terminate
 */
int sh_execute(char **args)
{
    int i;

    if (args[0] == NULL)
    {
    /*An empty command was entered.*/
    return (1);
    }

    for (i = 0; i < lsh_num_builtins(); i++)
    {
    if (strcmp(args[0], builtin_str[i]) == 0)
    {
      return ((*builtin_func[i])(args));
      }
      }

    return (sh_launch(args));
}

/*
  * @brief Read a line of input from stdin.
   *@return The line from stdin.
 */
char *sh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf (stderr, "Error\n");
        exit (EXIT_FAILURE);
    }
    while(1)
    {
        /*read a char*/
        c = getchar();
        /*replace EOF with NULL and return*/
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return (buffer);
        }else
        {
            buffer[position] = c;
        }
        position++;

        /*if size exceeded buffer reallocated*/
        if (position >= bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }

}


/*
   *@brief Split a line into tokens (very naively).
   *@param line The line.
   *@return Null-terminated array of tokens.
 */
char **sh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token;

  if (!tokens)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) 
    {
    tokens[position] = token;
    position++;

    if (position >= bufsize)
    {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char *));
      if (!tokens)
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return (tokens);
}

void loop(void)
{
    char *line;
    char **args;
    int status;
    
    /*
    *read cmd entered by user
    *parse cmd to understand cmd and arg
    *exec cmd
    */

    do{
        printf("Bigus_Dickus@root$~");
        line = sh_read_line();
        /*args is array of strings*/
        args =  sh_split_line(line);
        status = sh_execute(args);
        /*freeing memory*/
        free(line);
        free(args);

    } while (status);
}


int main(int argc, char **argv)
{
    /* code */
    /*load config files*/
    /*run Read Eval Print(REPL) loop*/
    loop();
    /*perform shutdown cleanup(free mem)*/
    return (EXIT_SUCCESS);
}
