#include "declare.h"

/**
 * main - entry point
 * @ab: arg count
 * @ad: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ab, char **ad)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ab == 2)
	{
		fd = open(ad[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_print_error_string(ad[0]);
				_print_error_string(": 0: Can't open ");
				_print_error_string(ad[1]);
				_write_error_char('\n');
				_write_error_char(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_fd = fd;
	}
	populate_environment_list(info);
	readHistory(info);
	shell_loop(info, ad);
	return (EXIT_SUCCESS);
}