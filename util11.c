#include "shell.h"

/**
* mystrcat - function that concatenates two strings
* @dest: first string
* @src: second string
* Return: first string + second string
*/
char *mystrcat(char *dest, char *src)
{
char *s = dest;

while (*dest != '\0')
{
dest++;
}

while (*src != '\0')
{
*dest = *src;
dest++;
src++;
}
*dest = '\0';
return (s);
}


/**
* mystrncmp - function that compares n amount of characters of two strings
* @str1: first string
* @str2: second string
* @num: amount of characters to compare
* Return: 1 if the strings don't match otherwise 0
*/
int mystrncmp(const char *str1, const char *str2, size_t num)
{
size_t i;
if (str1 == NULL)
return (-1);
for (i = 0; i < num && str2[i] != '\0'; i++)
{
if (str1[i] != str2[i])
return (1);
}
return (0);
}


/**
* mystrdup - duplicate a string
* @src: string
* Return: duplicated string or Null if failed
*/
char *mystrdup(char *src)
{
size_t src_len = strlen(src);
size_t i = 0;
char *dest;
dest = (char *)malloc((src_len + 1) * sizeof(char));
if (!dest)
{
return (NULL);
}

while (src[i] != '\0')
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';

return (dest);
}



