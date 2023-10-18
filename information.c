#include "shell.h"

/**
 * clear_inf - initializes info_v struct
 * @inf: struct address
 */
void clear_inf(info_v *inf)
{
	inf->arga = NULL;
	inf->argb = NULL;
	inf->pth = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes info_v struct
 * @inf: struct address
 * @av: argument vector
 */
void set_inf(info_v *inf, char **av)
{
	int i = 0;

	inf->filename = av[0];
	if (inf->arga)
	{
		inf->argb = strtw(inf->arga, " \t");
		if (!inf->argb)
		{
			inf->argb = malloc(sizeof(char *) * 2);
			if (inf->argb)
			{
				inf->argb[0] = _strdup(inf->arga);
				inf->argb[1] = NULL;
			}
		}
		for (i = 0; inf->argb && inf->argb[i]; i++)
			;
		inf->argc = i;

		replace_aliasa(inf);
		replace_varsa(inf);
	}
}

/**
 * free_inf - frees info_v struct fields
 * @inf: struct address
 * @al: true if freeing all fields
 */
void free_inf(info_v *inf, int al)
{
	f_free(inf->argb);
	inf->argb = NULL;
	inf->pth = NULL;
	if (al)
	{
		if (!inf->cmdbuf)
			free(inf->arga);
		if (inf->enva)
			free_list(&(inf->enva));
		if (inf->hist)
			free_list(&(inf->hist));
		if (inf->alias_n)
			free_list(&(inf->alias_n));
		f_free(inf->environment);
			inf->environment = NULL;
		b_free((void **)inf->cmdbuf);
		if (inf->read_fd > 2)
			close(inf->read_fd);
		_putchar(BUF_FLUSH);
	}
}

