#include "shell.h"

/**
 * _getenv - retrieves env variable that matches input string
 * @input: input string
 * @env: local environmental variables
 * Return: string of env variable
 */
char *_getenv(char *input, char **env)
{
	register int i = 0;
	char *ch, *rght;

	while (env[i])
	{
		ch = _strtok(env[i], "=");
		if (_strcmp(ch, input) == 0)
		{
			rght = _strtok(NULL, "=");
			return (rght);
		}
		i++;
	}
	return (NULL);
}

