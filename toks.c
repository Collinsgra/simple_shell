#include "shell.h"
/**
 * _tokenizer - function  that separates the string using separater.
 * @data: program's data ptr
 * Return: an array of diff_parts of strngs
 */
void _tokenizer(program_datas *data)
{
	char *separater = " \t";
	int i, n, counter = 2, length;

	length = string_length(data->in_putln);
	if (length)
	{
		if (data->in_putln[length - 1] == '\n')
			data->in_putln[length - 1] = '\0';
	}

	for (i = 0; data->in_putln[i]; i++)
	{
		for (n = 0; separater[n]; n++)
		{
			if (data->in_putln[i] == separater[n])
				counter++;
		}
	}

	data->toks = malloc(counter * sizeof(char *));
	if (data->toks == NULL)
	{
		perror(data->name_progr);
		exit(errno);
	}
	i = 0;
	data->toks[i] = string_dup(_strtok(data->in_putln, separater));
	data->command_in = string_dup(data->toks[0]);
	while (data->toks[i++])
	{
		data->toks[i] = string_dup(_strtok(NULL, separater));
	}
}
