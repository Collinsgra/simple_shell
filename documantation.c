#include "shell.h"

/**
 * free_recurrent_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_recurrent_data(program_datas *data)
{
	if (data->toks)
		free_array_of_pointers(data->toks);
	if (data->in_putln)
		free(data->in_putln);
	if (data->command_in)
		free(data->command_in);

	data->in_putln = NULL;
	data->command_in = NULL;
	data->toks = NULL;
}

/**
 * free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_all_data(program_datas *data)
{
	if (data->descrip != 0)
	{
		if (close(data->descrip))
			perror(data->name_progr);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->environs);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
