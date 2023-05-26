#include "shell.h"

/**
 * my_helpfunc - retrieves instruction on how to use builtin
 * @info: input info
 * Return: Always 1
 */
int my_helpfunc(config *info)
{
	type_b help_arr[] = {
		{"exit", exit_help},
		{"env", env_help},
		{"history", story_help},
		{"alias", alias_help},
		{"cd", cd_help},
		{"setenv", setenv_help},
		{"unsetenv", unsetenv_help},
		{"help", my_helphelp},
		{NULL, NULL}
	};
	register int i = 0, j = 1, argCount = countArgs(info->args);
	bool foundCommand = false;

	if (argCount == 1)
		return (dis_helpmenu());
	while (j < argCount)
	{
		i = 0;
		while (help_arr[i].command)
		{
			if (_strcmp(info->args[j], help_arr[i].command) == 0)
			{
				foundCommand = true;
				help_arr[i].func(info);
				break;
			}
			i++;
		}
		j++;
	}
	if (foundCommand == false)
	{
		errno = ENOBUILTIN;
		error_handler(info);
	}
	return (1);
}

/**
 * dis_helpmenu - displays available help options
 * Return: Always 1
 */
int dis_helpmenu(void)
{
	char str[81] = "Type help [built-in]\n\nIncluded built-ins:";
	char *str2 = "\n\n\texit\n\tenv\n\tcd\n\tsetenv\n\tunsetenv\n\thelp\n";

	_strcat(str, str2);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}


/**
 * exit_help - instructions on how to exit
 * @info: input info
 * Return: Always 1
 */
int exit_help(config *info)
{
	char str[82] = "exit: exit [n]\n\tExit the shell.\n\n\t";
	char *str2 = "Exit with a status of n, or if n is omitted, 0.\n";

	(void)info;
	_strcat(str, str2);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * env_help - instructions on how to exit
 * @info: input info
 * Return: Always 1
 */
int env_help(config *info)
{
	char str[] = "env: env\n\tPrint the environment.\n";

	(void)info;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * story_help - instructions on how to exit
 * @info: input info
 * Return: Always 1
 */
int story_help(config *info)
{
	char str[] = "history: history\n\tNot supported in this version.\n";

	(void)info;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

