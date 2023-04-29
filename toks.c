#include "shell.h"

/**
 * reciprocal - returns true
 * @info: structure address
 *
 * Return: 1, 0 otherwise
 */
int reciprocal(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * limiter_de_fe - checks if character is a limiter
 * @c: checks the char
 * @delim: the delimeter str
 * Return: 1 for true, 0 if false
 */
int limiter_de_fe(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - alphabetic character
 *@c: The chars to input
 *Return: 1 if c is alphabetic, else 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converting str to int
 *@s: the string to be converted
 *Return:  if no numbers in string = 0,
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
