#include "declare.h"


/**
 * _print_error_string - Prints a string to the standard error stream.
 *
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */

void _print_error_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_write_error_char(str[i]);
		i++;
	}
}


/**
 * _write_error_char - Writes a character to the standard error stream.
 *
 * @c: The character to print.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and sets errno appropriately.
 */

int _write_error_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}


/**
 * _write_to_fd - Writes a character to the specified file descriptor.
 *
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and sets errno appropriately.
 */

int _write_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}


/**
 * _print_to_fd - Prints a string to the specified file descriptor.
 *
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */

int _print_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _write_to_fd(*str++, fd);
	}
	return (i);
}