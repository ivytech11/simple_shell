#include "shell.h"

/**
 * updateOld - updates OLDPWD to current PWD
 * @info: input info
 * Return: index in linked list of PWD on success -
 * If PWD or OLDPWD does not exist in environ vars,
 * return -1
 */
int updateOld(config *info)
{
	register int pwdIndex = 0, index = 0;
	static char old[BUFSIZE];
	char *current = NULL;

	_strcat(old, "OLD");
	pwdIndex = sear_node(info->env, "PWD");
	if (pwdIndex == -1)
	{
		return (-1);
	}
	current = getnode_Index(info->env, pwdIndex);
	_strcat(old, current);
	insert_nullbyte(old, _strlen(current) + 4);
	free(current);
	index = sear_node(info->env, "OLDPWD");
	if (index == -1)
	{
		return (-1);
	}
	delnode_ndex(&info->env, index);
	addnode_index(&info->env, index, old);
	insert_nullbyte(old, 0);
	return (pwdIndex);
}

/**
 * updateCur - updates PWD to accurately reflect current directory
 * @info: input info
 * @index: index in linked list of where to insert PWD env var
 * Return: true on success, false on failure
 */
bool updateCur(config *info, int index)
{
	static char tmp[BUFSIZE], cwd[BUFSIZE];

	getcwd(tmp, BUFSIZE);
	_strcat(cwd, "PWD=");
	_strcat(cwd, tmp);
	if (index > -1)
	{
		delnode_ndex(&info->env, index);
		addnode_index(&info->env, index, cwd);
	} else
		addnode_index(&info->env, 0, cwd);
	insert_nullbyte(tmp, 0);
	insert_nullbyte(cwd, 0);
	return (true);
}
