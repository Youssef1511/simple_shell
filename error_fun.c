#include "shell.h"

/**
 *_heputs - prints an input string
 * @strng: the string to be printed
 *
 * Return: Nothing
 */
void _heputs(char *strng)
{
	int i = 0;

	if (!strng)
		return;
	while (strng[i] != '\0')
	{
		_heputchar(strng[i]);
		i++;
	}
}

/**
 * _heputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _heputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfed - writes the character c to given fd
 * @c: The character to print
 * @fed: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfed(char c, int fed)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fed, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfed - prints an input string
 * @strng: the string to be printed
 * @fed: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfed(char *strng, int fed)
{
	int i = 0;

	if (!strng)
		return (0);
	while (*strng)
	{
		i += _putfed(*strng++, fed);
	}
	return (i);
}

