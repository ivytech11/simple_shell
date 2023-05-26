#include "shell.h"

/**
 * check_path - searches $PATH for directory of command
 * @info: input info
 * return: true if found, false if not
 */
bool check_path(config *info)
{
	register int len;
	static char buffer[BUFSIZE];
	struct stat st;
	char *tok, *copy, *delim = ":", *tmp;
	bool inLoop = false;

	if (check_cases(info))
		return (true);
	copy = _strdup(info->path);
	tok = _strtok(copy, delim);
	while (tok)
	{
		tmp = inLoop ? tok - 2 : tok;
		if (*tmp == 0 && stat(info->args[0], &st) == 0)
		{
			info->fullPath = info->args[0];
			free(copy);
			return (true);
		}
		len = _strlen(tok) + _strlen(info->args[0]) + 2;
		_strcat(buffer, tok);
		_strcat(buffer, "/");
		_strcat(buffer, info->args[0]);
		insert_nullbyte(buffer, len - 1);
		if (stat(buffer, &st) == 0)
		{
			free(copy);
			info->fullPath = buffer;
			return (true);
		}
		insert_nullbyte(buffer, 0);
		tok = _strtok(NULL, delim);
		inLoop = true;
	}
	info->fullPath = info->args[0];
	free(copy);
	return (false);
}

/**
 * check_cases - helper func for check path to check edge cases
 * @info: input info
 * Return: true if found, false if not
 */
bool check_cases(config *info)
{
	char *copy;
	struct stat st;

	copy = _strdup(info->path);
	if (!copy)
	{
		info->fullPath = info->args[0];
		free(copy);
		return (true);
	}
	if (*copy == ':' && stat(info->args[0], &st) == 0)
	{
		info->fullPath = info->args[0];
		free(copy);
		return (true);
	}
	free(copy);
	return (false);
}
