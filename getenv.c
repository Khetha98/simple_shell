#include "declare.h"

/**
 * get_environment - Returns a copy of the
 *  environment variables as a string array.
 *
 * @info: Structure containing potential arguments
 *  used to maintain constant function prototype.
 *
 * Return: The string array representing the environment.
 */


char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listToStrings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_environment_variable - Remove an environment variable.
 *
 * @info: Structure containing potential arguments
 *  used to maintain constant function prototype.
 * @variable: The environment variable to remove.
 *
 * Return: 1 on successful removal, 0 otherwise.
 */

int unset_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = string_starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->env_changed = deleteNodeAtIndex(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * set_environment_variable - Initializes a
 *  new environment variable or modifies an existing one.
 *
 * @info: Structure containing potential
 *  arguments. Used to maintain constant function prototype.
 * @variable: The environment variable property.
 * @value: The environment variable value.
 *
 * Return: Always 0.
 */

int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(str_length(variable) + str_length(value) + 2);
	if (!buffer)
		return (1);

	string_copy(buffer, variable);
	string_concatenate(buffer, "=");
	string_concatenate(buffer, value);

	node = info->env;
	while (node)
	{
		p = string_starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addNode_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}