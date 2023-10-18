#include "shell.h"

/**
 * b_free - frees a pointer and NULLs the address
 * @point: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int b_free(void **point)
{
	if (point && *point)
	{
		free(*point);
		*point = NULL;
		return (1);
	}
	return (0);
}

