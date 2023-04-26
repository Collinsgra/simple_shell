#include "shell.h"

/**
 * xpand_vars - expanding variables
 * @data: a ptr to a structure of program's data
 *
 * Return: nothing, but sets errno.
 */
void xpand_vars(program_datas *data)
{
	int i, m;
	char line[BUFFER_SIZE] = {0}, increase[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->in_putln == NULL)
		return;
	buffer_add(line, data->in_putln);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_string(errno, increase, 10);
			buffer_add(line, increase);
			buffer_add(line, data->in_putln + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_string(getpid(), increase, 10);
			buffer_add(line, increase);
			buffer_add(line, data->in_putln + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (n = 1; line[i + n] && line[i + n] != ' '; n++)
				increase[n - 1] = line[i + n];
			temp = environ_get_key(increase, data);
			line[i] = '\0', increase[0] = '\0';
			buffer_add(increase, line + i + n);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, increase);
		}
	if (!string_compare(data->in_putln, line, 0))
	{
		free(data->in_putln);
		data->in_putln = string_dup(line);
	}
}

/**
 * xpand_subs - expands substitutes
 * @data: ptr to a structure of program's data
 *
 * Return: nothing, but sets errno.
 */
void xpand_subs(program_datas *data)
{
	int i, n, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, increase[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->in_putln == NULL)
		return;

	buffer_add(line, data->in_putln);

	for (i = 0; line[i]; i++)
	{
		for (n = 0; line[i + n] && line[i + n] != ' '; n++)
			increase[n] = line[i + n];
		increase[n] = '\0';

		temp = get_alias(data, increase);
		if (temp)
		{
			increase[0] = '\0';
			buffer_add(increase, line + i + n);
			line[i] = '\0';
			buffer_add(line, temp);
			line[string_length(line)] = '\0';
			buffer_add(line, increase);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->in_putln);
		data->in_putln = string_duplicate(line);
	}
}

/**
 * buffer_add - add string at end
 * @buffer: to be filled
 * @string_add: string copied in buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *string_add)
{
	int length, i;

	length = string_length(buffer);
	for (i = 0; string_add[i]; i++)
	{
		buffer[length + i] = string_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
