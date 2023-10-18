#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @strng: str field of node
 * @xn: node index used by history
 *
 * Return: size of list
 */
list_v *add_node(list_v **head, const char *strng, int xn)
{
	list_v *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_v));
	if (!new_head)
		return (NULL);
	_memoryset((void *)new_head, 0, sizeof(list_v));
	new_head->xn = xn;
	if (strng)
	{
		new_head->strng = _strdup(strng);
		if (!new_head->strng)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @strng: str field of node
 * @xn: node index used by history
 *
 * Return: size of list
 */
list_v *add_node_end(list_v **head, const char *strng, int xn)
{
	list_v *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_v));
	if (!new_node)
		return (NULL);
	_memoryset((void *)new_node, 0, sizeof(list_v));
	new_node->xn = xn;
	if (strng)
	{
		new_node->strng = _strdup(strng);
		if (!new_node->strng)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_v linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_v *h)
{
	size_t i = 0;

	while (h)
	{
		_putsa(h->strng ? h->strng : "(nil)");
		_putsa("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_v **head, unsigned int index)
{
	list_v *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->strng);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->strng);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_v **head_ptr)
{
	list_v *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->strng);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

