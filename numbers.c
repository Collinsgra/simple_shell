#include "shell.h"

/**
 * long_string - converts a num to a str.
 * @number: num to be converted
 * @string: to save number as str.
 * @base: converts number
 *
 * Return: Nothing.
 */
void long_string(long number, char *string, int base)
{
	int htm_l = 0, adverse = 0;
	long quotient = number;
	char letters[] = {"0123456789abcdefg"};

	if (quotient == 0)
		string[htm_l++] = '0';

	if (string[0] == '-')
		adverse = 1;

	while (quotient)
	{
		if (quotient < 0)
			string[htm_l++] = letters[-(quotient % base)];
		else
			string[htm_l++] = letters[quotient % base];
		quotient /= base;
	}
	if (adverse)
		string[htm_l++] = '-';

	string[htm_l] = '\0';
	string_rev(string);
}


/**
 * _atoi - converts a str to an int.
 *
 * @s: ptr to string
 * Return: 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}


	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_chars - count the same appearing characters in a string.
 *
 * @string: ptr to string
 * @character: string with  chars to be counted
 * Return: 0.
 */
int count_chars(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
