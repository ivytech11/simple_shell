#include "shell.h"

/**
 * error_handler - prints error message for shell
 * @info: the info config
 */
void error_handler(config *info)
{
	register int len;
	static char error[BUFSIZE];
	char *ptr, *alpha;

	alpha = itoa(info->lineCounter);
	_strcat(error, info->shellName);
	_strcat(error, ": ");
	_strcat(error, alpha);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, geterror_msg());
	if (info->args[1])
	{
		if (errno != EBADCD)
			_strcat(error, ": ");
		_strcat(error, info->args[1]);
	}
	_strcat(error, "\n");
	ptr = _strchr(error, '\n');
	len = ptr - error;
	write(STDERR_FILENO, error, len + 1);
	free(alpha);
	insert_nullbyte(error, 0);
}

/**
 * geterror_msg - matches errno to corresponding string
 * Return: string of error message
 */
char *geterror_msg(void)
{
	char *str;

	switch (errno)
	{
		case EBADCD:
			str = ": can't cd to ";
			break;
		case ENOENT:
			str = ": not found";
			break;
		case ENOSTRING:
			str = ": bad variable name";
			break;
		case EILLEGAL:
			str = ": Illegal number";
			break;
		case EWSIZE:
			str = ": invalid number of arguments";
			break;
		case ENOBUILTIN:
			str = ": type help for a list of built-ins";
			break;
		case EACCES:
			str = ": Permission denied";
			break;
		default:
			str = ": no error number assigned";
	}
	return (str);
}

/**
 * counter_dgt - count number of digits in a number
 * @num: input number
 * Return: number of digits
 */
unsigned int counter_dgt(int num)
{
	register int digits = 0;

	while (num > 0)
	{
		digits++;
		num /= 10;
	}
	return (digits);
}

/**
 * itoa - converts integer to string
 * @num: input integer
 * Return: string type of number
 */
char *itoa(unsigned int num)
{
	register int digits = 0;
	char *str;

	digits += counter_dgt(num);
	str = malloc(sizeof(char) * (digits + 1));
	if (!str)
	{
		perror("Malloc: failed\n");
		exit(errno);
	}
	insert_nullbyte(str, digits);
	while (num > 0)
	{
		str[digits - 1] = num % 10 + '0';
		num = num / 10;
		digits--;
	}
	return (str);
}
