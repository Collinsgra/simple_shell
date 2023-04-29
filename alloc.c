#include "shell.h"

/**
 * free_ptr - frees a ptr Null address
 * @ptr: addres
 *
 * Return: 1 freed, else 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
