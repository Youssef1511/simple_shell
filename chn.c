#include "shell.h"

/**
 * replace_string - replaces string
 * @oldd: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **oldd, char *new)
{
	free(*oldd);
	*oldd = new;
	return (1);
}


/**
 * check_chn - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chn(info_v *inf, char *buff, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (inf->cmdbuf_t == CMD_AND)
	{
		if (inf->stat)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (inf->cmdbuf_t == CMD_OR)
	{
		if (!inf->stat)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_aliasa - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_aliasa(info_v *inf)
{
	int i;
	list_v *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inf->alias_n, inf->argb[0], '=');
		if (!node)
			return (0);
		free(inf->argb[0]);
		p = _strchar(node->strng, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argb[0] = p;
	}
	return (1);
}

/**
 * replace_varsa - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_varsa(info_v *inf)
{
	int i = 0;
	list_v *node;

	for (i = 0; inf->argb[i]; i++)
	{
		if (inf->argb[i][0] != '$' || !inf->argb[i][1])
			continue;

		if (!_strcompare(inf->argb[i], "$?"))
		{
			replace_string(&(inf->argb[i]),
				_strdup(convert_number(inf->stat, 10, 0)));
			continue;
		}
		if (!_strcompare(inf->argb[i], "$$"))
		{
			replace_string(&(inf->argb[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->enva, &inf->argb[i][1], '=');
		if (node)
		{
			replace_string(&(inf->argb[i]),
				_strdup(_strchar(node->strng, '=') + 1));
			continue;
		}
		replace_string(&inf->argb[i], _strdup(""));

	}
	return (0);
}


/**
 * is_chn - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chn(info_v *inf, char *buff, size_t *p)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		inf->cmdbuf_t = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		inf->cmdbuf_t = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		inf->cmdbuf_t = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

