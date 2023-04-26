#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_alias(program_datas *data, char *alias)
{
	int i, n, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = string_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (string_compare(data->alias_list[i], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (n = 0; data->alias_list[i][n]; n++)
				{
					buffer[n] = data->alias_list[i][n];
					if (data->alias_list[i][n] == '=')
						break;
				}
				buffer[n + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + n + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, delete | show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(program_datas *data, char *name)
{
	int i, alias_length;


	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = string_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (string_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{
			return (data->alias_list[i] + alias_length + 1);
		}
	}

	return (NULL);

}

/**
 * set_alias - add, or overwrite
 * @alias_string: alias to set in the form 
 * @data: program's data structure
 * Return: 0 if success, or other nums if declared args
 */
int set_alias(char *alias_string, program_datas *data)
{
	int i, n;
	char buffer[250] = {'0'}, *temp = NULL;


	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);

	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = get_alias(data, alias_string + i + 1);
			break;
		}


	for (n = 0; data->alias_list[n]; n++)
		if (string_compare(buffer, data->alias_list[n], i) &&
			data->alias_list[n][i] == '=')
		{
			free(data->alias_list[n]);
			break;
		}


	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[n] = string_dup(buffer);
	}
	else
		data->alias_list[n] = string_dup(alias_string);
	return (0);
}
