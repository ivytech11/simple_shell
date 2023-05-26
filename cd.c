#include "shell.h"

/**
 * my_cdfunc - execute cd builtin
 * @info: input info
 * Return: 1 on success, 0 on failure
 */
int my_cdfunc(config *info)
{
	register uint count = 0;
	bool ableToChange = false;

	count = countArgs(info->args);
	if (count == 1)
		ableToChange = cdToHome(info);
	else if (count == 2 && _strcmp(info->args[1], "-") == 0)
		ableToChange = cdToPrevious(info);
	else
		ableToChange = cdToCustom(info);
	if (ableToChange)
		updateEnviron(info);
	return (1);
}

/**
 * cdToHome - change directory to home
 * @info: input info
 * Return: true on success, false on failure
 */
bool cdToHome(config *info)
{
	register int i;
	char *str, *ptr;

	i = sear_node(info->env, "HOME");
	if (i == -1)
	{
		return (true);
	}
	str = getnode_Index(info->env, i);
	ptr = _strchr(str, '=');
	ptr++;
	chdir(ptr);
	free(str);
	return (true);
}

/**
 * cdToPrevious - change directory to previous directory -
 * address is found in OLDPWD env var
 * @info: input info
 * Return: true on success, false on failure
 */
bool cdToPrevious(config *info)
{
	register int i;
	char *str, *ptr;
	char *current = NULL;

	current = getcwd(current, 0);
	i = sear_node(info->env, "OLDPWD");
	if (i == -1)
	{
		chdir(current);
		write(STDOUT_FILENO, current, _strlen(current));
		dsly_newline();
		return (true);
	}
	str = getnode_Index(info->env, i);
	ptr = _strchr(str, '=');
	ptr++;
	chdir(ptr);
	write(STDOUT_FILENO, ptr, _strlen(ptr));
	dsly_newline();
	free(str);
	return (true);
}

/**
 * cdToCustom - change directory to what user inputs in
 * @info: input info
 * Return: true on success, false on failure
 */
bool cdToCustom(config *info)
{
	register int changeStatus;

	changeStatus = chdir(info->args[1]);
	if (changeStatus == -1)
	{
		errno = EBADCD;
		error_handler(info);
		return (false);
	}
	return (true);
}

/**
 * updateEnviron - change environmental variables
 * @info: input info
 * Return: true on success false on failure
 */
bool updateEnviron(config *info)
{
	register int i;

	i = updateOld(info);
	updateCur(info, i);
	return (true);
}

