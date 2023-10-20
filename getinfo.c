#include "declare.h"

/**
 * initialize_info - Initializes the info_t structure.
 *
 * @info: Address of the info_t struct to be initialized.
 */

void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}



/**
 * setupInfo - Initializes the info_t structure with arguments and other data.
 *
 * @info: A pointer to the info_t structure to be populated.
 * @argumentVector: The argument vector (av) containing command line arguments.
 */

void setupInfo(info_t *info, char **argumentVector)
{
	int i = 0;

	info->program_name = argumentVector[0];
	if (info->arg)
	{
		info->argv = tokenizeString(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicateString(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * cleanupInfo - Frees memory associated with the info_t structure fields.
 *
 * @info: A pointer to the info_t structure to be cleaned up.
 * @freeAll: If true, free all fields; otherwise, free only specific fields.
 */

void cleanupInfo(info_t *info, int freeAll)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (freeAll)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		freeStringArray(info->environ);
		info->environ = NULL;
		freeBuffer((void **)info->cmd_buf);
		if (info->read_fd > 2)
			close(info->read_fd);
		_write_error_char(BUFFER_FLUSH);
	}
}
