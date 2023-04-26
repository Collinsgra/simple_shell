#include "shell.h"

/**
 * environ_get_key - gets value of an environvars
 * @key: environ vars
 * @data: program's data structure
 * Return: a ptr to the value of the variable or NULL
 */
char *environ_get_key(char *key, program_datas *data)
{
	int i, key_length = 0;


	if (key == NULL || data->environs == NULL)
		return (NULL);


	key_length = string_length(key);

	for (i = 0; data->environs[i]; i++)
	{
		if (string_compare(key, data->environs[i], key_length) &&
		 data->environs[i][key_length] == '=')
		{
			return (data->environs[i] + key_length + 1);
		}
	}

	return (NULL);
}

/**
 * environ_set_key - overwrites values
 * or make one if doesnt exist
 * @key: name of vars to set
 * @value: new
 * @data: program's data structures
 * Return: 1 if NULL, 2 if error, 0 if success.
 */

int environ_set_key(char *key, char *value, program_datas *data)
{
	int i, key_length = 0, is_new_key = 1;


	if (key == NULL || value == NULL || data->environs == NULL)
		return (1);


	key_length = string_length(key);

	for (i = 0; data->environs[i]; i++)
	{
		if (string_compare(key, data->environs[i], key_length) &&
		 data->environs[i][key_length] == '=')
		{
			is_new_key = 0;

			free(data->environs[i]);
			break;
		}
	}

	data->environs[i] = string_concat(string_dup(key), "=");
	data->environs[i] = string_concat(data->environs[i], value);

	if (is_new_key)
	{
		data->environs[i + 1] = NULL;
	}
	return (0);
}

/**
 * environ_remove_key - remove a key from env
 * @key: the key to be removed
 * @data: program's data structure
 * Return: 1 if key was removed, 0 if does not exist;
 */
int environ_remove_key(char *key, program_datas *data)
{
	int i, key_length = 0;


	if (key == NULL || data->environs == NULL)
		return (0);


	key_length = string_length(key);

	for (i = 0; data->environs[i]; i++)
	{
		if (string_compare(key, data->environs[i], key_length) &&
		 data->environs[i][key_length] == '=')
		{
			free(data->environs[i]);


			i++;
			for (; data->environs[i]; i++)
			{
				data->environs[i - 1] = data->environs[i];
			}

			data->environs[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - prints current environ
 * @data: structure for program's data
 * Return: nothing
 */
void print_environ(program_datas *data)
{
	int n;

	for (n = 0; data->environs[n]; n++)
	{
		_print(data->environs[n]);
		_print("\n");
	}
}
