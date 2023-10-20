#include "declare.h"

/**
 * input_buffer - Buffers a chain of commands.
 *
 * @info: The parameter struct.
 * @buffer: Address of the buffer.
 * @buffer_length: Address of the buffer length.
 *
 * Return: The number of bytes read.
 */

ssize_t input_buffer(info_t *info, char **buffer, size_t *buffer_length)
{
	ssize_t read_bytes = 0;
	size_t length = 0;

	if (!*buffer)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signal_handler);
		read_bytes = getline(buffer, &length, stdin);

		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0';
				read_bytes--;
			}
			info->line_count_flag = 1;
			remove_comments(*buffer);
			buildHistoryList(info, *buffer, info->histCount++);
		}
	}
	return read_bytes;
}

/**
 * get_input - Retrieves a line without the newline character.
 *
 * @info: The parameter struct.
 *
 * Return: The number of bytes read.
 */

ssize_t get_input(info_t *info)
{
	static char *buffer; /* The ';' command chain buffer */
	static size_t buffer_length = 0;
	static size_t i, j, len;
	ssize_t read_bytes = 0;
	char **buffer_p = &(info->arg), *p;

	_write_error_char(BUFFER_FLUSH);
	read_bytes = input_buffer(info, &buffer, &buffer_length);
	if (read_bytes == -1) /* EOF */
		return (-1);

	if (buffer_length)
	{
		j = i;
		p = buffer + i;

		check_chain_continuation(info, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chain_delimiter(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p;
		return (str_length(p));
	}

	*buffer_p = buffer;
	return read_bytes;
}

/**
 * read_buffer - Reads a buffer.
 *
 * @info: The parameter struct.
 * @buf: The buffer.
 * @i: The size.
 *
 * Return: The number of bytes read.
 */

ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t read_bytes = 0;

	if (*i)
		return 0;
	read_bytes = read(info->read_fd, buf, READ_BUF_SIZE);
	if (read_bytes >= 0)
		*i = read_bytes;
	return read_bytes;
}

/**
 * _getline - Gets the next line of input from STDIN.
 *
 * @info: The parameter struct.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: The number of bytes read.
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_bytes = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		read_bytes = *length;

	if (i == len)
	{
		i = len = 0;
	}

	read_bytes = read_buffer(info, buf, &len);

	if (read_bytes == -1 || (read_bytes == 0 && len == 0))
		return (-1);

	c = my_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, read_bytes, read_bytes ? read_bytes + k : k + 1);

	if (!new_p)
	{
		return (p ? free(p), -1 : -1);
	}

	if (read_bytes)
	{
		my_strncat(new_p, buf + i, k - i);
	}
	else
	{
		my_strncpy(new_p, buf + i, k - i + 1);
	}

	read_bytes += k - i;
	i = k;
	p = new_p;

	if (length)
	{
		*length = read_bytes;
	}

	*ptr = p;
	return read_bytes;
}

/**
 * signal_handler - Blocks Ctrl-C.
 *
 * @sig_num: The signal number.
 *
 * Return: void
 */

void signal_handler(__attribute__((unused))int sig_num)
{
	print_string("\n");
	print_string("$ ");
	_write_error_char(BUFFER_FLUSH);
}

