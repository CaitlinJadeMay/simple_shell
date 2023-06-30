#include "shell.h"

/**
* find_command_path -  Search In $PATH for executable command
* @cmd: Parsed input
* Return: 0 on success or  1 on failure  0
*/
int find_command_path(char **command)
{
char *path, *path_value, *command_path;
struct stat buffer;

path = mygetenv("PATH");
path_value = mystrtok(path, ":");
while (path_value != NULL)
{
command_path = build_path(*command, path_value);
if (stat(command_path, &buffer) == 0)
{
*command = mystrdup(command_path);
free(command_path);
free(path);
return (0);
}
free(command_path);
path_value = mystrtok(NULL, ":");
}
free(path);
free(path_value);
return (1);
}

/**
* build_path - Build command
* @token: Executable command
* @value: Directory conatining Command
* Return: Parsed full path of command or NULL if failed
*/
char *build_path(char *token, char *value)
{
char *cmd;
size_t len;

len = str_len(value) + str_len(token) + 2;
cmd = malloc(sizeof(char) * len);
if (cmd == NULL)
{
free(cmd);
return (NULL);
}

memset(cmd, 0, len);

cmd = mystrcat(cmd, value);
cmd = mystrcat(cmd, "/");
cmd = mystrcat(cmd, token);

return (cmd);
}

/**
* mygetenv - Gets the value of environment variable by name
* @name: Environment variable name
* Return: The value of the environment variable or NULL if failed
*/
char *mygetenv(char *name)
{
size_t name_length, value_length;
char *value;
int i, j, k;

name_length = str_len(name);
for (i = 0; environ[i]; i++)
{
if (mystrncmp(name, environ[i], name_length) == 0)
{
value_length = str_len(environ[i]) - name_length;
value = malloc(sizeof(char) * value_length);
if (!value)
{
free(value);
perror("unable to allocate memory");
return (NULL);
}

j = 0;
k = name_length + 1;
while (environ[i][k])
{
value[j] = environ[i][k];
j++;
k++;
}
value[j] = '\0';

return (value);
}
}

return (NULL);
}


/**
* print_number - Prints unsigned integers using myputchar function
* @n: Unsigned integer to be printed
*/
void print_number(unsigned int n)
{
unsigned int x = n;

if ((x / 10) > 0)
print_number(x / 10);

myputchar(x % 10 + '0');
}

/**
* print_integer - Prints integers using myputchar function
* @n: Integer to be printed
*/
void print_integer(int n)
{
unsigned int x = n;

if (n < 0)
{
myputchar('-');
x = -x;
}
if ((x / 10) > 0)
print_number(x / 10);

myputchar(x % 10 + '0');
}

