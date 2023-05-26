#include "shell.h"

/**
 * m_envfunc - prints the environment
 * @info: input info
 * Return: Always 1
 */
int m_envfunc(config *info)
{
	showlist(info->env);
	return (1);
}

/**
 * set_envfunc - adds env variable if it does not exist;
 * modify env variable if it does
 * @info: input info
 * Return: Always 1
 */
int set_envfunc(config *info)
{
	register int index, len;
	static char buffer[BUFSIZE];

	if (countArgs(info->args) != 3)
	{
		errno = EWSIZE;
		error_handler(info);
		return (1);
	}
	len = _strlen(info->args[1]) + _strlen(info->args[2]) + 2;
	_strcat(buffer, info->args[1]);
	_strcat(buffer, "=");
	_strcat(buffer, info->args[2]);
	insert_nullbyte(buffer, len - 1);
	index = sear_node(info->env, info->args[1]);
	if (index == -1)
	{
		addnode_end(&info->env, buffer);
		insert_nullbyte(buffer, 0);
		return (1);
	}
	delnode_ndex(&info->env, index);
	addnode_index(&info->env, index, buffer);
	insert_nullbyte(buffer, 0);
	return (1);
}

/**
 * unset_envfunc - deletes env variable if exists;
 * will only accept valid variables names
 * @info: input info
 * Return: Always 1
 */
int unset_envfunc(config *info)
{
	register int foundVar, i = 1;
	bool foundMatch = false;

	while (info->args[i])
	{
		if (_isalpha(info->args[i][0]) || info->args[i][0] == '_')
		{
			foundVar = sear_node(info->env, info->args[i]);
			if (foundVar > -1)
			{
				delnode_ndex(&info->env, foundVar);
				foundMatch = true;
			}
		}
		i++;
	}
	if (foundMatch == false)
	{
		errno = ENOSTRING;
		error_handler(info);
	}
	return (1);
}

/**
 * _isalpha - checks if c is an alphabetic character
 * @c: potential alphabetical value
 * Return: if c is a letter, returns 1. Otherwise, return 0.
 */
int _isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (1);
	else
		return (0);
}
