#include "shell.h"

/**
 * _print - writes array of chars in standard o.
 * @string: ptr to char[]
 * Return: num of bytes writed |
 * On error, -1 is returned, and errno is set well.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, string_length(string)));
}
/**
 * _printe - writes chars[] in stderror
 * @string: ptr to the chars[]
 * Return: num of bytes writed |
 * On error, -1 is returned, and errno is set well
 */
int _printp(char *string)
{
	return (write(STDERR_FILENO, string, string_length(string)));
}

/**
 * _print_error - writes chars[] in stderror
 * @data: program's data'a pointter
 * @errorcode: error code printed
 * Return: the number of bytes writed or .-1 is returned, and errno is set
 */
int _print_error(int errorcode, program_datas *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->name_progr);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->toks[0]);
		if (errorcode == 2)
			_printe(": Number error: ");
		else
			_printe(": cannot cd to this ");
		_printe(data->toks[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->name_progr);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_in);
		_printe(": not available\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->name_progr);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_in);
		_printe(": Access denied\n");
	}
	return (0);
}
