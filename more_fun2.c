#include "shell.h"

/**
 * _erratoia - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoia(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - prints an error message
 * @inf: the parameter & return info struct
 * @etr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_err(info_v *inf, char *etr)
{
	_heputs(inf->filename);
	_heputs(": ");
	print_dd(inf->line_c, STDERR_FILENO);
	_heputs(": ");
	_heputs(inf->argb[0]);
	_heputs(": ");
	_heputs(etr);
}

/**
 * print_dd - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dd(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _heputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @n: number
 * @bs: base
 * @f: argument flags
 *
 * Return: string
 */
char *convert_number(long int n, int bs, int f)
{
	static char *arr;
	static char buff[50];
	char siyn = 0;
	char *point;
	unsigned long x = n;

	if (!(f & CONVERT_UNSIGNED) && n < 0)
	{
		x = -n;
		siyn = '-';

	}
	arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	point = &buff[49];
	*point = '\0';

	do	{
		*--point = arr[x % bs];
		x /= bs;
	} while (x != 0);

	if (siyn)
		*--point = siyn;
	return (point);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}

