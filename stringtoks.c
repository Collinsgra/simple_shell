#include "shell.h"
/**
 * str_tok - separates strings with separators
 * @line: It´s ptr to array we receive in _function.
 * @separ: marker str in parts.
 * Return: A pointer to the created token
*/
char *str_tok(char *line, char *separ)
{
	int n;
	static char *str;
	char *copystring;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (n = 0; separ[n] != '\0'; n++)
		{
			if (*str == separ[n])
			break;
		}
		if (separ[n] == '\0')
			break;
	}
	copystring = str;
	if (*copystring == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (n = 0; separ[n] != '\0'; n++)
		{
			if (*str == separ[n])
			{
				*str = '\0';
				str++;
				return (copystring);
			}
		}
	}
	return (copystring);
}
