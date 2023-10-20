#include "declare.h"



/**
 * main - is the entry point
 * @ac: is the arg count
 * @av: is the arg vector
 *
 * Return: returns 0 when success,  but 1 when error
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
				the_print('\n');
				the_print(BUFFER_FLUSH);
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
