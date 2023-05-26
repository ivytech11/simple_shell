#include "shell.h"

/**
 * findBuiltIns - validates if command is builtin and executes
 * @info: input info
 * Return: true if found, false if not
 */
bool findBuiltIns(config *info)
{
	register int i = 0;
	type_b getBuiltIns[] = {
		{"exit", my_exitfunc},
		{"env", m_envfunc},
		{"history", my_storyfunc},
		{"alias", my_aliasfunc},
		{"cd", my_cdfunc},
		{"setenv", set_envfunc},
		{"unsetenv", unset_envfunc},
		{"help", my_helpfunc},
		{NULL, NULL}
	};

	while (getBuiltIns[i].command)
	{
		if (_strcmp(info->args[0], getBuiltIns[i].command) == 0)
		{
			getBuiltIns[i].func(info);
			free_args_buffer(info);
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * my_exitfunc - exits the application
 * @info: input info
 * Return: 1 on success, 0 on failure
 */
int my_exitfunc(config *info)
{
	register int argCount, exitStatus;

	argCount = countArgs(info->args);
	if (argCount == 1)
	{
		free_memb(info);
		if (info->errorStatus)
			exit(info->errorStatus);
		exit(EXIT_SUCCESS);
	}
	else if (argCount > 1)
	{
		exitStatus = _atoi(info->args[1]);
		if (exitStatus == -1)
		{
			errno = EILLEGAL;
			info->errorStatus = 2;
			error_handler(info);
			return (0);
		}
		free_memb(info);
		exit(exitStatus);
	}
	return (1);
}

/**
 * my_storyfunc - displays command history
 * @info: input info
 * Return: 1 on success, 0 on failure
 */
int my_storyfunc(config *info)
{
	char *str = "Currently in development\n";

	(void)info;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * my_aliasfunc - displays local aliases
 * @info: input info
 * Return: 1 on success, 0 on failure
 */
int my_aliasfunc(config *info)
{
	char *str = "Currently in development\n";

	(void)info;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
