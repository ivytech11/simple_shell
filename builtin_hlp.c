#include "shell.h"

/**
* countArgs - count the number of arguments
* @args: input array of strings
* Return: number of strings
*/
int countArgs(char **args)
{
	register int i = 0;

	while (args[i])
		i++;
	return (i);
}

/**
* _atoi - change string to an integer
* @s: input string
* Return: -1 if it's not a valid number, else the converted number
*/
int _atoi(char *s)
{
	register int i = 0;
	unsigned long number = 0;

	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			number = number * 10 + s[i] - '0';
		else
			return (-1);
		i++;
	}
	if (number > INT_MAX)
	{
		return (-1);
	}
	return (number);
}
