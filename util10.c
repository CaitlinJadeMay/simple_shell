#include "shell.h"


/**
* mystrcmp - function that compares two string
* @str1: first string
* @str2: second string
* Return: 0 if identical otherwise how much diffrent
*/
int mystrcmp(char *str1, char *str2)
{
int cmp = 0;
int i = 0;
int len1 = str_len(str1);
int len2 = str_len(str2);

if (len1 != len2)
return (1);
if (str1 == NULL || str2 == NULL)
return (1);

while (str1[i])
{
if (str1[i] != str2[i])
{
cmp = str1[i] - str2[i];
break;
}
else
{
i++;
}
}

return (cmp);
}

/**
* myisalpha - function to check if c is alphabet
* @ch: character to check
* Return: 1 if true 0 if false
*/
int myisalpha(int ch)
{
int result = 0;
int lowerCase = (ch >= 97) && (ch <= 122);
int upperCase = (ch >= 65) && (ch <= 90);

if (lowerCase || upperCase)
{
result = 1;
}

return (result);
}


/**
* myitoa - funciton that convert integer to character
* @num: integer to convert
* Return: character pointer
*/
char *myitoa(unsigned int num)
{
int num_len = 1;
int index = 0;
char *str;

if (num == 0)
num_len = 1;
else
{
unsigned int temp = num;
while (temp != 0)
{
temp /= 10;
num_len++;
}
}
str = malloc(num_len + 2);

if (!str)
{
free(str);
return (NULL);
}
*str = '\0';

while (num)
{
str[index] = (num % 10) + '0';
num /= 10;
index++;
}

array_reverse(str, num_len);
str[index] = '\0';

return (str);
}

/**
* array_reverse - function to reverse an array
* @arr: array to reverse
* @len: length of array
*/
void array_reverse(char *arr, int len)
{
int i = 0;
char tmp;

while (i < (len / 2))
{
tmp = arr[i];
arr[i] = arr[(len - 1) - i];
arr[(len - 1) - i] = tmp;

i++;
}
}

