#include "declare.h"

/**
 * my_history - Displays the history list, one command per line,
 *              preceded with line numbers, starting at 0.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0.
 */

int my_history(info_t *info)
{
	printList(info->history);
	return (0);
}


/**
 * unset_custom_alias - Unsets a custom alias.
 *
 * @info: Parameter structure.
 * @alias_str: The custom alias string to unset.
 *
 * Return: Always 0 on success, 1 on error.
 */

int unset_custom_alias(info_t *info, char *alias_str)
{
	char *equals_ptr, saved_char;
	int result;

	equals_ptr = my_strchr(alias_str, '=');
	if (!equals_ptr)
		return (1);

	saved_char = *equals_ptr;
	*equals_ptr = 0;
	result = deleteNodeAtIndex(&(info->alias), getNodeIndex(info->alias, nodeStartsWith(info->alias, alias_str, -1)));
	*equals_ptr = saved_char;

	return result;
}

/**
 * set_custom_alias - Sets a custom alias.
 *
 * @info: Parameter structure.
 * @alias_str: The custom alias string to set.
 *
 * Return: Always 0 on success, 1 on error.
 */

int set_custom_alias(info_t *info, char *alias_str)
{
	char *equals_ptr;

	equals_ptr = my_strchr(alias_str, '=');
	if (!equals_ptr)
		return (1);

	if (!*++equals_ptr)
		return unset_custom_alias(info, alias_str);

	unset_custom_alias(info, alias_str);
	return (addNode_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_custom_alias - Prints a custom alias string.
 *
 * @alias_node: The alias node to print.
 *
 * Return: Always 0 on success, 1 on error.
 */

int print_custom_alias(list_t *alias_node)
{
	char *alias_start = NULL, *alias_value = NULL;

	if (alias_node)
	{
		alias_start = my_strchr(alias_node->str, '=');
		for (alias_value = alias_node->str; alias_value <= alias_start; alias_value++)
			_write_error_char(*alias_value);
		_write_error_char('\'');
		print_string(alias_start + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - Mimics the alias built-in (man alias).
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0.
 */

int my_alias(info_t *info)
{
	int i = 0;
	char *alias_start = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_custom_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		alias_start = my_strchr(info->argv[i], '=');
		if (alias_start)
			set_custom_alias(info, info->argv[i]);
		else
			print_custom_alias(nodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}