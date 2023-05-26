#include "shell.h"

/**
 * alias_help - instructions on how to exit
 * @info: input info
 * Return: Always 1
 */
int alias_help(config *info)
{
	char str[] = "alias: alias\n\tNot supported in this version.\n";

	(void)info;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * cd_help - instructions on how to exit
 * @info: input info
 * Return: Always 1
 */
int cd_help(config *info)
{
	char str[192] = "cd: cd [destination]\n\t";
	char *str2 = "Change directory to target destination.\n\t";
	char *str3 = "If [destination] is ommitted, user will taken to home.\n\t";
	char *str4 = "If \"-\" is used as second argument, user will be taken to ";
	char *str5 = "last directory.\n";

	(void)info;
	_strcat(str, str2);
	_strcat(str, str3);
	_strcat(str, str4);
	_strcat(str, str5);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * setenv_help - instructions on how to exit
 * @info: input info
 * Return: Always 1
 */
int setenv_help(config *info)
{
	char str[186] = "setenv: setenv [var] [value]\n\t";
	char *str2 = "Set or update a variable in the environment.\n\n\t";
	char *str3 = "Creates a variable [var] with [value]. ";
	char *str4 = "If the [var] already exists in the environment, ";
	char *str5 = "the value is updated.\n";

	(void)info;
	_strcat(str, str2);
	_strcat(str, str3);
	_strcat(str, str4);
	_strcat(str, str5);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * unsetenv_help - instructions on how to exit
 * @info: input info
 * Return: Always 1
 */
int unsetenv_help(config *info)
{
	char str[116] = "unsetenv: unsetenv [var]\n\t";
	char *str2 = "Unset a variable in the environment.\n\n\t";
	char *str3 = "[var] is an existing variable in the environment.\n";

	(void)info;
	_strcat(str, str2);
	_strcat(str, str3);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * my_helphelp - instructions on how to exit
 * @info: input info
 * Return: Always 1
 */
int my_helphelp(config *info)
{
	char str[129] = "help: help [built-in]\n\t";
	char *str2 = "Display information about built-in commands.\n\n\t";
	char *str3 = "If [built-in] is not specified, print a list of built-ins.\n";

	(void)info;
	_strcat(str, str2);
	_strcat(str, str3);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

