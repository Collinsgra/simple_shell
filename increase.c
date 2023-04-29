#include "shell.h"

/**
 **setMemory - fills mem
 *@s:  pointer to mem
 *@b: byte to vill *s with
 *@n: the amount to be filled
 *Return: (s) a pointer to mem
 */
char *setMemory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_str_str - frees str
 * @pp: stringx2
 */
void free_str_str(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc -  memory realloc
 * @ptr: pointer to last malloc
 * @prev_size: last block byte size 
 * @brand_size: new block byte size
 *
 * Return: pointer.
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int brand_size)
{
	char *p;

	if (!ptr)
		return (malloc(brand_size));
	if (!brand_size)
		return (free(ptr), NULL);
	if (brand_size == prev_size)
		return (ptr);

	p = malloc(brand_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < brand_size ? prev_size : brand_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}
