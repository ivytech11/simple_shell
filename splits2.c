#include "shell.h"

/**
 * free_memb - frees info config members
 * @info: input info
 */
void free_memb(config *info)
{
	if (info->env)
		free_list(info->env);
	if (info->args)
		free_args(info->args);
	if (info->buffer)
		free(info->buffer);
}

/**
 * free_args_buffer - frees args and buffer
 * @info: input info
 */
void free_args_buffer(config *info)
{
	free_args(info->args);
	free(info->buffer);
}

/**
 * free_list - frees a linked list
 * @head: double pointer to head of list
 */
void free_list(linked_l *head)
{
	linked_l *current;
	linked_l *tmp;

	if (!head)
		return;
	current = head;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		free(tmp->string);
		free(tmp);
	}
	head = NULL;
}

/**
 * free_args - helper func that frees double pointer arg
 * @args: array of char pointers
 */
void free_args(char **args)
{
	register uint i = 0;

	while (args[i])
		free(args[i++]);
	free(args);
}

