#include "shell.h"

/**
 * main - entry point for application
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	config info;

	(void)ac;
	signal(SIGINT, sigint_handler);
	configInit(&info);
	info.shellName = av[0];
	shell(&info);
	return (0);
}

/**
 * configInit - initialize member values for config struct
 * @info: input info
 * Return: info with initialized members
 */
config *configInit(config *info)
{
	info->env = gen_linkedlist(environ);
	info->envList = NULL;
	info->args = NULL;
	info->buffer = NULL;
	info->path = _getenv("PATH", environ);
	info->fullPath = NULL;
	info->lineCounter = 0;
	info->shellName = NULL;
	info->errorStatus = 0;
	return (info);
}
