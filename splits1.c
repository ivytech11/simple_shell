#include "shell.h"

/**
 * split_string - splits string into an array of strings
 * separated by spaces
 * @info: input info
 * Return: true if able to split, false if not
 */
bool split_string(config *info)
{
	register unsigned int i = 0;
	char *tok, *cpy;

	if (counter_words(info->buffer) == 0)
	{
		info->args = NULL;
		free(info->buffer);
		return (false);
	}
	info->args = malloc((counter_words(info->buffer) + 1) * sizeof(char *));
	cpy = _strdup(info->buffer);
	tok = _strtok(cpy, " ");
	while (tok)
	{
		info->args[i] = _strdup(tok);
		tok = _strtok(NULL, " ");
		i++;
	}
	info->args[i] = NULL;
	free(cpy);
	return (true);
}

/**
 * counter_words - count number of words in a string
 * @str: input string
 * Return: number of words
 */
unsigned int counter_words(char *str)
{
	register int words = 0;
	bool wordOn = false;

	while (*str)
	{
		if (its_space(*str) && wordOn)
			wordOn = false;
		else if (!its_space(*str) && !wordOn)
		{
			wordOn = true;
			words++;
		}
		str++;
	}
	return (words);
}

/**
 * its_space - determines if char is a space
 * @c: input char
 * Return: true or false
 */
bool its_space(char c)
{
	return (c == ' ');
}

