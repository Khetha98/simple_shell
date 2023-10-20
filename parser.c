#include "declare.h"




/**
 * isExecutableCommand - Checks if a file is an executable command.
 *
 * @info: The info struct (not used).
 * @path: Path to the file to be checked.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */

int isExecutableCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info; // Not used
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateSubstring - Duplicates a substring from a string.
 *
 * @pathStr: The source string (e.g., PATH).
 * @start: Starting index of the substring.
 * @stop: Stopping index of the substring.
 *
 * Return: Pointer to a new buffer containing the duplicated substring.
 */
char *duplicateSubstring(char *pathStr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathStr[i] != ':')
			buffer[k++] = pathStr[i];
	buffer[k] = 0;
	return buffer;
}

/**
 * findCommandInPath - Finds a command in the PATH string.
 *
 * @info: The info struct (not used).
 * @pathStr: The PATH string.
 * @command: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */

char *findCommandInPath(info_t *info, char *pathStr, char *command)
{
	int i = 0, currPos = 0;
	char *path;

	if (!pathStr)
		return NULL;
	if ((str_length(command) > 2) && string_starts_with(command, "./"))
	{
		if (isExecutableCommand(info, command))
			return command;
	}
	while (1)
	{
		if (!pathStr[i] || pathStr[i] == ':')
		{
			path = duplicateSubstring(pathStr, currPos, i);
			if (!*path)
				string_concatenate(path, command);
			else
			{
				string_concatenate(path, "/");
				string_concatenate(path, command);
			}
			if (isExecutableCommand(info, path))
				return path;
			if (!pathStr[i])
				break;
			currPos = i;
		}
		i++;
	}
	return NULL;
}