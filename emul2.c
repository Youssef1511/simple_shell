#include "shell.h"

/**
 * _myhist - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhist(info_v *inf)
{
	print_list(inf->hist);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @strng: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_v *inf, char *strng)
{
	char *p, c;
	int ret;

	p = _strchar(strng, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(inf->alias_n),
		get_node_index(inf->alias_n, node_starts_with(inf->alias_n, strng, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @strng: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_v *inf, char *strng)
{
	char *p;

	p = _strchar(strng, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(inf, strng));

	unset_alias(inf, strng);
	return (add_node_end(&(inf->alias_n), strng, 0) == NULL);
}

/**
 * _myaliasa - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int _myaliasa(info_v *inf)
{
	int i = 0;
	char *p = NULL;
	list_v *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias_n;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argb[i]; i++)
	{
		p = _strchar(inf->argb[i], '=');
		if (p)
			set_alias(inf, inf->argb[i]);
		else
			print_alias(node_starts_with(inf->alias_n, inf->argb[i], '='));
	}

	return (0);
}


/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_v *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchar(node->strng, '=');
		for (a = node->strng; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_putsa(p + 1);
		_putsa("'\n");
		return (0);
	}
	return (1);
}


