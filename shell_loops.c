#include "shell.h"

/**
 * shell - simple shell
 * @info: input info
 */
void shell(config *info)
{
	while (true)
	{
		check_getline(info);
		if (split_string(info) == false)
			continue;
		if (findBuiltIns(info) == true)
			continue;
		check_path(info);
		fork_exect(info);
	}
}

/**
 * check_getline - check stdin and retrieves next line; handles
 * prompt display
 * @info: input info
 */
void check_getline(config *info)
{
	register int len;
	size_t bufferSize = 0;
	char *ptr, *ptr2;

	info->args = NULL;
	info->envList = NULL;
	info->lineCounter++;
	if (isatty(STDIN_FILENO))
		dsly_Prp();
	len = getline(&info->buffer, &bufferSize, stdin);
	if (len == EOF)
	{
		free_memb(info);
		if (isatty(STDIN_FILENO))
			dsly_newline();
		if (info->errorStatus)
			exit(info->errorStatus);
		exit(EXIT_SUCCESS);
	}
	ptr = _strchr(info->buffer, '\n');
	ptr2 = _strchr(info->buffer, '\t');
	if (ptr || ptr2)
		insert_nullbyte(info->buffer, len - 1);
	strp_comments(info->buffer);
}

/**
 * strp_comments - remove comments from input string
 * @str: input string
 * Return: length of remaining string
 */
void strp_comments(char *str)
{
	register int i = 0;
	bool notFirst = false;

	while (str[i])
	{
		if (i == 0 && str[i] == '#')
		{
			insert_nullbyte(str, i);
			return;
		}
		if (notFirst)
		{
			if (str[i] == '#' && str[i - 1] == ' ')
			{
				insert_nullbyte(str, i);
				return;
			}
		}
		i++;
		notFirst = true;
	}
}

/**
 * fork_exect - fork current info and execute processes
 * @info: input info
 */
void fork_exect(config *info)
{
	int status;
	pid_t f1 = fork();

	cvrt_lltoarr(info);
	if (f1 == -1)
	{
		perror("error\n");
		free_memb(info);
		free_args(info->envList);
		exit(1);
	}
	if (f1 == 0)
	{
		if (execve(info->fullPath, info->args, info->envList) == -1)
		{
			error_handler(info);
			free_memb(info);
			free_args(info->envList);
			if (errno == ENOENT)
				exit(127);
			if (errno == EACCES)
				exit(126);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			info->errorStatus = WEXITSTATUS(status);
		free_args_buffer(info);
		free_args(info->envList);
	}
}

/**
 * cvrt_lltoarr - convert linked list to array
 * @info: input info
 */
void cvrt_lltoarr(config *info)
{
	register int i = 0;
	size_t count = 0;
	char **envList = NULL;
	linked_l *tmp = info->env;

	count = list_lenght(info->env);
	envList = malloc(sizeof(char *) * (count + 1));
	if (!envList)
	{
		perror("Malloc failed\n");
		exit(1);
	}
	while (tmp)
	{
		envList[i] = _strdup(tmp->string);
		tmp = tmp->next;
		i++;
	}
	envList[i] = NULL;
	info->envList = envList;
}

