#include "shell.h"


/**
 * _unsetenva - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenva(info_v *inf, char *var)
{
	list_v *node = inf->enva;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startswith(node->strng, var);
		if (p && *p == '=')
		{
			inf->env_ch = delete_node_at_index(&(inf->enva), i);
			i = 0;
			node = inf->enva;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_ch);
}

/**
 * _setenva - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenva(info_v *inf, char *var, char *value)
{
	char *buf = NULL;
	list_v *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlength(var) + _strlength(value) + 2);
	if (!buf)
		return (1);
	_strcopy(buf, var);
	_strdog(buf, "=");
	_strdog(buf, value);
	node = inf->enva;
	while (node)
	{
		p = startswith(node->strng, var);
		if (p && *p == '=')
		{
			free(node->strng);
			node->strng = buf;
			inf->env_ch = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->enva), buf, 0);
	free(buf);
	inf->env_ch = 1;
	return (0);
}

/**
 * get_environa - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environa(info_v *inf)
{
	if (!inf->environment || inf->env_ch)
	{
		inf->environment = list_to_strings(inf->enva);
		inf->env_ch = 0;
	}

	return (inf->environment);
}

