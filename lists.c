#include "declare.h"

/**
 * addNode - Add a new node to the start of the list.
 *
 * @head: A pointer to the address of the head node.
 * @str: The string to be stored in the new node.
 * @num: The index used by history.
 * Return: A pointer to the newly created node.
 */


list_t *addNode(list_t **head, const char *str, int num)
{
	list_t *newNode;

	if (!head)
		return (NULL);
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = string_duplicate(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	newNode->next = *head;
	*head = newNode;
	return (newNode);
}


/**
 * addNode_end - Add a new node to the end of the list.
 *
 * @head: A pointer to the address of the head node.
 * @str: The string to be stored in the new node.
 * @num: The index used by history.
 * Return: A pointer to the newly created node.
 */

list_t *addNode_end(list_t **head, const char *str, int num)
{
	list_t *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = string_duplicate(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 * printListStr - Print only the 'str' element of a list_t linked list.
 *
 * @h: A pointer to the first node.
 * Return: The size of the list.
 */

size_t printListStr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * deleteNodeAtIndex - Delete a node at a given index.
 *
 * @head: A pointer to the address of the head node.
 * @index: The index of the node to delete.
 * Return: 1 on success, 0 on failure.
 */

int deleteNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *node, *prevNode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prevNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prevNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * freeList - Free all nodes of a list.
 *
 * @headPtr: A pointer to the address of the head node.
 * Return: void
 */

void freeList(list_t **headPtr)
{
	list_t *node, *nextNode, *head;

	if (!headPtr || !*headPtr)
		return;
	head = *headPtr;
	node = head;
	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}
	*headPtr = NULL;
}