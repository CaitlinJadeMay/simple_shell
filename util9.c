
#include "shell.h"




/**
* simple_shell_history - write file with user inputs
* @input: user input
* Return: 0 on success -1 if failed
*/
int simple_shell_history(char *input)
{
const char *filename = ".simple_shell_history";
ssize_t file_descriptor, bytes_written;
int input_length = 0;

if (filename == NULL)
return (-1);

file_descriptor = open(filename, O_CREAT | O_RDWR | O_APPEND, 00600);
if (file_descriptor < 0)
return (-1);

if (input != NULL)
{
while (input[input_length] != '\0')
input_length++;

bytes_written = write(file_descriptor, input, input_length);
if (bytes_written < 0)
{
close(file_descriptor);
return (-1);
}
}

close(file_descriptor);
return (1);
}




/**
* separate_by_semi_col - Separates command recieved from stdin by ;
* @input: String gathered from stdin
* Return: Parsed strings to be used as commands
*/
char **separate_by_semi_col(char *input)
{
char **commands;
char *cmd;
int i;
int buffer_size = BUFFER;

if (input[0] == ' ' && input[str_len(input)] == ' ')
exit(0);
if (input == NULL)
return (NULL);

commands = malloc(sizeof(char *) * buffer_size);
if (!commands)
{
free(commands);
perror("hsh");
return (NULL);
}

cmd = mystrtok(input, ";&");
i = 0;
while (cmd)
{
commands[i] = cmd;
cmd = mystrtok(NULL, ";&");
i++;
}

commands[i] = NULL;

return (commands);
}


/**
* myputchar - function that writes the character to stdout
* @c: The character to print
* Return: character to standard output
*/
int myputchar(char c)
{
return (write(1, &c, 1));
}





/**
* str_len - function that counts the length of a string
* @s: string input
* Return: length of string
*/
int str_len(char *s)
{
int i;

for (i = 0; s[i] != '\0'; i++)
{
continue;
}
return (i);
}

/**
* myatoi - function to convert string to a integer
* @s: string input
* Return: converted integer
*/
int myatoi(char *s)
{
int i = 0, j = 1, k;
unsigned int l = 0;

while (s[i] != '\0')
{
if (s[i] == '-')
{
return (2);
}
k = s[i] - '0';

if (l > 0 && !(k >= 0 && k <= 9))
break;

if (k >= 0 && k <= 9)
l = l * 10 + k;

i++;
}
l *= j;
return (l);
}



