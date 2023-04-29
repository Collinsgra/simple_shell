#include "shell.h"

/**
 **copy_str - copies a str
 *@_destination: the _destinationination str to be written
 *@src: srce str
 *@n: the char will be written
 *Return: the conc str
 */
char *copy_str(char *_destination, char *src, int n)
{
	int i, x;
	char *s = _destination;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		_destination[i] = src[i];
		i++;
	}
	if (i < n)
	{
		x = i;
		while (x < n)
		{
			_destination[x] = '\0';
			x++;
		}
	}
	return (s);
}

/**
 **conc_str - conc two str
 *@_destination: the first string
 *@src: second str
 *@n: the byet to be exausted
 *Return: the conc str
 */
char *conc_str(char *_destination, char *src, int n)
{
	int i, x;
	char *s = _destination;

	i = 0;
	x = 0;
	while (_destination[i] != '\0')
		i++;
	while (src[x] != '\0' && x < n)
	{
		_destination[i] = src[x];
		i++;
		x++;
	}
	if (x < n)
		_destination[i] = '\0';
	return (s);
}

/**
 **chars_str - locates a char to str
 *@s: the str is psd
 *@c: is the char to be checked
 *Return: (s) a ptr to mem s
 */
char *chars_str(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
