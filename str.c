#include "shell.h"

/**
 * string__length - returns the length size of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int string__length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * compare_string - compares
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int compare_string(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if direction starts with compass
 * @compass: string to search
 * @direction: the substring to find
 *
 * Return: address of next char of compass or NULL
 */
char *starts_with(const char *compass, const char *direction)
{
	while (*direction)
		if (*direction++ != *compass++)
			return (NULL);
	return ((char *)compass);
}

/**
 * string_conc - concatenates two strings
 * @_destination: the _destinationination buffer
 * @src: the source buffer
 *
 * Return: pointer to _destinationination buffer
 */
char *string_conc(char *_destination, char *src)
{
	char *ret = _destination;

	while (*_destination)
		_destination++;
	while (*src)
		*_destination++ = *src++;
	*_destination = *src;
	return (ret);
}
