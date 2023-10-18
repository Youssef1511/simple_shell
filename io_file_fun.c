#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(info_v *inf)
{
	char *buf, *dir;

	dir = _getenva(inf, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlength(dir) + _strlength(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcopy(buf, dir);
	_strdog(buf, "/");
	_strdog(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_v *inf)
{
	ssize_t fd;
	char *filename = get_hist_file(inf);
	list_v *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = inf->hist; node; node = node->next)
	{
		_putsfed(node->strng, fd);
		_putfed('\n', fd);
	}
	_putfed(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(info_v *inf)
{
	int i, last = 0, linec = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(inf);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_list(inf, buf + last, linec++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(inf, buf + last, linec++);
	free(buf);
	inf->histc = linec;
	while (inf->histc-- >= HIST_MAX)
		delete_node_at_index(&(inf->hist), 0);
	renumber_hist(inf);
	return (inf->histc);
}

/**
 * build_hist_list - adds entry to a hist linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linec: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_list(info_v *inf, char *buf, int linec)
{
	list_v *node = NULL;

	if (inf->hist)
		node = inf->hist;
	add_node_end(&node, buf, linec);

	if (!inf->hist)
		inf->hist = node;
	return (0);
}

/**
 * renumber_hist - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_hist(info_v *inf)
{
	list_v *node = inf->hist;
	int i = 0;

	while (node)
	{
		node->xn = i++;
		node = node->next;
	}
	return (inf->histc = i);
}

