#include "shell.h"

/**
 * **string_to_words - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_to_words(char *str, char *d)
{
	int i, x, k, m, word_nums = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!limiter_de_fe(str[i], d) && (limiter_de_fe(str[i + 1], d) || !str[i + 1]))
			word_nums++;

	if (word_nums == 0)
		return (NULL);
	s = malloc((1 + word_nums) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, x = 0; x < word_nums; x++)
	{
		while (limiter_de_fe(str[i], d))
			i++;
		k = 0;
		while (!limiter_de_fe(str[i + k], d) && str[i + k])
			k++;
		s[x] = malloc((k + 1) * sizeof(char));
		if (!s[x])
		{
			for (k = 0; k < x; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[x][m] = str[i++];
		s[x][m] = 0;
	}
	s[x] = NULL;
	return (s);
}

/**
 * **string_to_words2 -divide a string to 2
 * @str: the str
 * @d: the delim
 * Return: ptrs, or NULL on failure
 */
char **string_to_words2(char *str, char d)
{
	int i, x, k, m, word_nums = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			word_nums++;
	if (word_nums == 0)
		return (NULL);
	s = malloc((1 + word_nums) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, x = 0; x < word_nums; x++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[x] = malloc((k + 1) * sizeof(char));
		if (!s[x])
		{
			for (k = 0; k < x; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[x][m] = str[i++];
		s[x][m] = 0;
	}
	s[x] = NULL;
	return (s);
}
