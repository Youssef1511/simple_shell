#include "shell.h"

/**
 * _myenva - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenva(info_v *inf)
{
	print_list_str(inf->enva);
	return (0);
}

/**
 * _getenva - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenva(info_v *inf, const char *name)
{
	list_v *node = inf->enva;
	char *p;

	while (node)
	{
		p = startswith(node->strng, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenva - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenva(info_v *inf)
{
	if (inf->argc != 3)
	{
		_heputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenva(inf, inf->argb[1], inf->argb[2]))
		return (0);
	return (1);
}

/**
 * populate_enva_list - populates env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_enva_list(info_v *inf)
{
	list_v *node = NULL;
	size_t i;

	for (i = 0; environment[i]; i++)
		add_node_end(&node, environment[i], 0);
	inf->enva = node;
	return (0);
}

/**
 * _myunsetenva - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenva(info_v *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_heputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenva(inf, inf->argb[i]);

	return (0);
}



