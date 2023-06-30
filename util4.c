#include "shell.h"


/**
* mystrtok - function that extracts tokens of a string
* @str: string
* @delim: delim
* Return: pointer to the next token or NULL
*/
char *mystrtok(char *str, const char *delim)
{
static char *token_string, *next_token;
unsigned int token_index = 0;
if (str != NULL)
next_token = str;
token_string = next_token;
if (token_string == NULL)
return (NULL);
while (token_string[token_index] != '\0')
{
if (match_char(token_string[token_index], delim) == 0)
break;
token_index++;
}
if (next_token[token_index] == '\0' || next_token[token_index] == '#')
{
next_token = NULL;
return (NULL);
}
token_string = next_token + token_index;
next_token = token_string;
token_index = 0;
while (next_token[token_index] != '\0')
{
if (match_char(next_token[token_index], delim) == 1)
break;
token_index++;
}

if (next_token[token_index] == '\0')
next_token = NULL;
else
{
next_token[token_index] = '\0';
next_token = next_token + token_index + 1;
if (*next_token == '\0')
next_token = NULL;
}

return (token_string);
}


/**
* change_dir - Changes directory
* @cmd: Parsed command
* @st: Status of last command executed
* Return: 0 on success 1 if failed (For OLDPWD Always 0 incase of no OLDPWD)
*/
int change_dir(char **cmd, __attribute__((unused))int st)
{
int value = -1;
char cwd[PATH_MAX];

if (cmd[1] == NULL)
value = chdir(getenv("HOME"));
else if (mystrcmp(cmd[1], "-") == 0)
{
value = chdir(getenv("OLDPWD"));
}
else
value = chdir(cmd[1]);

if (value == -1)
{
perror("hsh");
return (-1);
}
else if (value != -1)
{
getcwd(cwd, sizeof(cwd));
setenv("OLDPWD", getenv("PWD"), 1);
setenv("PWD", cwd, 1);
}
return (0);
}

/**
* dis_env - Display enviroment variable
* @cmd: parsed command
* @st: status of last command executed
* Return: Always 0
*/
int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int st)
{
size_t i;
int len;

for (i = 0; environ[i] != NULL; i++)
{
len = str_len(environ[i]);
write(1, environ[i], len);
write(STDOUT_FILENO, "\n", 1);
}
return (0);
}

/**
* echo_bul - execute echo cases
* @st: statue of last command executed
* @cmd: parsed command
* Return: Always 1 Or execute normal echo
*/
int echo_bul(char **cmd, int st)
{
char *path;
unsigned int pid = getppid();

if (mystrncmp(cmd[1], "$?", 2) == 0)
{
print_integer(st);
MYPRINT("\n");
}
else if (mystrncmp(cmd[1], "$$", 2) == 0)
{
print_number(pid);
MYPRINT("\n");
}
else if (mystrncmp(cmd[1], "$PATH", 5) == 0)
{
path = mygetenv("PATH");
MYPRINT(path);
MYPRINT("\n");
free(path);
}
else
return (execute_echo_command(cmd));

return (1);
}

