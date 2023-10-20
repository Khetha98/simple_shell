#include "declare.h"

/**
 * getHistoryFile - Get the history file path.
 *
 * @info: A pointer to the info_t structure.
 * Return: A dynamically allocated string containing the history file path.
 */

char *getHistoryFile(info_t *info)
{
	char *buf, *homeDir;

	homeDir = get_environment_variable(info, "HOME=");
	if (!homeDir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_length(homeDir) + str_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, homeDir);
	string_concatenate(buf, "/");
	string_concatenate(buf, HIST_FILE);
	return (buf);
}

/**
 * writeHistory - Write history to a file.
 *
 * @info: A pointer to the info_t structure.
 * Return: 1 on success, -1 on failure.
 */

int writeHistory(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		print_stringfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readHistory - Read history from a file.
 *
 * @info: A pointer to the info_t structure.
 * Return: The new history count, or 0 on failure.
 */

int readHistory(info_t *info)
{
	int i, last = 0, lineCount = 0;
	ssize_t fd, rdLen, fileSize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fileSize = st.st_size;
	if (fileSize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fileSize + 1));
	if (!buf)
		return (0);
	rdLen = read(fd, buf, fileSize);
	buf[fileSize] = 0;
	if (rdLen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fileSize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildHistoryList(info, buf + last, lineCount++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(info, buf + last, lineCount++);
	free(buf);
	info->histCount = lineCount;
	while (info->histCount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	renumberHistory(info);
	return (info->histCount);
}

/**
 * buildHistoryList - Add an entry to the history linked list.
 *
 * @info: A pointer to the info_t structure.
 * @buf: The buffer to add to the history.
 * @lineCount: The history line count.
 * Return: Always 0.
 */

int buildHistoryList(info_t *info, char *buf, int lineCount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	addNodeEnd(&node, buf, lineCount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberHistory - Renumber the history linked list after changes.
 *
 * @info: A pointer to the info_t structure.
 * Return: The new history count.
 */

int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histCount = i);
}