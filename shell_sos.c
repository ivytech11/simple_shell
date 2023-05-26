#include "shell.h"

/**
 * insert_nullbyte - inserts null byte at given index
 * @str: input string
 * @index: index to insert null byte
 */
void insert_nullbyte(char *str, unsigned int index)
{
	str[index] = '\0';
}

/**
 * dsly_Prp - displays shell prompt
 */
void dsly_Prp(void)
{
	write(STDERR_FILENO, "$ ", 2);
}

/**
 * dsly_newline - displays new line
 */
void dsly_newline(void)
{
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * sigint_handler - catches SIGINT signal and reset signal
 * @sigint: signal from stdint
 */
void sigint_handler(int sigint)
{
	(void)sigint;
	signal(SIGINT, sigint_handler);
	dsly_newline();
	dsly_Prp();
	fflush(stdout);
}

