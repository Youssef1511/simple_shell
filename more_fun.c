#include "shell.h"

/**
 * interact - returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interact(info_v *inf)
{
	return (isatty(STDIN_FILENO) && inf->read_fd <= 2);
}

/**
 * is_dell - checks if character is a delimeter
 * @c: the char to check
 * @dell: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_dell(char c, char *dell)
{
	while (*dell)
		if (*dell++ == c)
			return (1);
	return (0);
}

/**
 *_isalph - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalph(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoia - converts a string to an integer
 *@si: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoia(char *si)
{
	int i, siyn = 1, f = 0, out;
	unsigned int res = 0;

	for (i = 0;  si[i] != '\0' && f != 2; i++)
	{
		if (si[i] == '-')
			siyn *= -1;

		if (si[i] >= '0' && si[i] <= '9')
		{
			f = 1;
			res *= 10;
			res += (si[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (siyn == -1)
		out = -res;
	else
		out = res;

	return (out);
}

