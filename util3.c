#include "shell.h"

/**
* mygetline - read input from standard input by user
* Return: the input on a buffer
*/
char *mygetline(void)
{
int i = 0, rd, buffsize = BUFFER;
char c = 0, *buffer, *buf;

buffer = malloc(buffsize);
if (buffer == NULL)
{
free(buffer);
return (NULL);
}
while (c != EOF && c != '\n')
{
fflush(stdin);
rd = read(STDIN_FILENO, &c, 1);
if (rd == 0)
{
free(buffer);
exit(EXIT_SUCCESS);
}
buffer[i] = c;
if (buffer[0] == '\n')
return ("\0");
if (i >= buffsize)
{
buffer = realloc(buffer, buffsize + 2);
if (buffer == NULL)
{
free(buffer);
return (NULL);
}
}
i++;
}
buffer[i] = '\0';
buf = remove_space(buffer);
free(buffer);
remove_after_hash(buf);
return (buf);
}




/**
* remove_space - Modifies the input string to remove preceeding whitespaces
* @str: Input to be modifies
* Return: Returns the modified string
*/
char *remove_space(char *str)
{
int i = 0, j = 0;
char *buff;

buff = malloc(sizeof(char) * (str_len(str) + 1));
if (buff == NULL)
{
free(buff);
return (NULL);
}
while (str[i] == ' ')
{
i++;
}
while (str[i + 1] != '\0')
{
buff[j] = str[i];
i++;
j++;
}
buff[j] = '\0';
if (buff[0] == '\0' || buff[0] == '#')
{
free(buff);
return ("\0");
}
return (buff);
}

/**
* remove_after_hash - function that removes everything after '#'
* @buff: input buffer
* Return: nothing
*/
void remove_after_hash(char *buff)
{
int i = 0;

while (buff[i] != '\0')
{
if (buff[i] == '#' && buff[i - 1] == ' ' && buff[i + 1] == ' ')
{
buff[i] = '\0';
}
i++;
}
}

/**
* match_char - function that checks if a character matchs any character
* @ch: character to check
* @string: string of delimiters
* Return: 1 on success, 0 on failure
*/
unsigned int match_char(char ch, const char *string)
{
unsigned int i = 0;

while (string[i] != '\0')
{
if (ch == string[i])
return (1);
i++;
}

return (0);
}

