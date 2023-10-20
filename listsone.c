#include "declare.h"

/**
 * listLength - Determines the length of a linked list.
 *
 * @h: A pointer to the first node.
 * Return: Size of the list.
 */

size_t listLength(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * listToStrings - Converts a linked list of strings into an array of strings.
 *
 * @head: A pointer to the first node.
 * Return: An array of strings.
 */
char **listToStrings(list_t *head)
{
	list_t *node = head;
	size_t i = listLength(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = string_copy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * printList - Prints all elements of a list_t linked list.
 *
 * @h: A pointer to the first node.
 * Return: Size of the list.
 */
size_t printList(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		print_string(convertNumber(h->num, 10, 0));
		_write_error_char(':');
		_write_error_char(' ');
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodeStartsWith - Returns the node whose string starts with a prefix.
 *
 * @node: A pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 * Return: Matching node or NULL.
 */

list_t *nodeStartsWith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - Gets the index of a node.
 *
 * @head: A pointer to the list head.
 * @node: A pointer to the node.
 * Return: Index of the node or -1.
 */

ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}