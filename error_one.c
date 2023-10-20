#include "declare.h"

/**
 * str_to_int - Converts a string to an integer.
 *
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in the string, converted number otherwise.
 *         -1 on error.
 */

int str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}


/**
 * print_error_message - Prints an error message.
 *
 * @info: The information struct containing parameters and return values.
 * @error_string: String containing the specified error type.
 */

void print_error_message(info_t *info, char *error_string)
{
	_print_error_string(info->program_name);
	_print_error_string(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_print_error_string(": ");
	_print_error_string(info->argv[0]);
	_print_error_string(": ");
	_print_error_string(error_string);
}

/**
 * print_decimal - Prints a decimal (integer) number in base 10.
 *
 * @input: The integer to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */

int print_decimal(int input, int fd)
{
	int (*print_char)(char) = _write_to_fd;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		print_char = _write_error_char;
	if (input < 0)
	{
		absolute_value = -input;
		print_char('-');
		count++;
	}
	else
		absolute_value = input;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			print_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - Converts a number to a string.
 *
 * @num: The number to convert.
 * @base: The base for the conversion.
 * @flags: Flags for the conversion.
 *
 * Return: The converted string.
 */

char *convert_to_string(long int num, int base, int flags)
{
	static char *charset;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	charset = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = charset[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - Replaces the first instance of '#' with '\0' in the string.
 *
 * @buf: Address of the string to modify.
 */

void remove_first_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}