#include "shell.h"

/**
* _function - read 1 line from prompt.
* @data: program's data struct
*
* Return: reads bytes.
*/
int _function(program_datas *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;


	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{

		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}


		bytes_read = read(data->descrip, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);


		i = 0;
		do {
			array_commands[i] = string_dup(str_tok(i ? NULL : buff, "\n;"));

			i = check_logic_ops(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}


	data->in_putln = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (string_length(data->in_putln));
}


/**
* check_logic_ops - checks and split for && and || operators
* @array_commands: array of the commands.
* @i: index in the array_commands to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: index of last command.
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int n;


	for (n = 0; array_commands[i] != NULL  && array_commands[i][n]; n++)
	{
		if (array_commands[i][n] == '&' && array_commands[i][n + 1] == '&')
		{

			temp = array_commands[i];
			array_commands[i][n] = '\0';
			array_commands[i] = string_dup(array_commands[i]);
			array_commands[i + 1] = string_dup(temp + n + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			n = 0;
		}
		if (array_commands[i][n] == '|' && array_commands[i][n + 1] == '|')
		{

			temp = array_commands[i];
			array_commands[i][n] = '\0';
			array_commands[i] = string_dup(array_commands[i]);
			array_commands[i + 1] = string_dup(temp + n + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			n = 0;
		}
	}
	return (i);
}
