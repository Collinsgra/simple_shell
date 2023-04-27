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
 * _printp - writes chars[] in stderror
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

	long_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printp(data->name_progr);
		_printp(": ");
		_printp(n_as_string);
		_printp(": ");
		_printp(data->toks[0]);
		if (errorcode == 2)
			_printp(": Number error: ");
		else
			_printp(": cannot cd to this ");
		_printp(data->toks[1]);
		_printp("\n");
	}
	else if (errorcode == 127)
	{
		_printp(data->name_progr);
		_printp(": ");
		_printp(n_as_string);
		_printp(": ");
		_printp(data->command_in);
		_printp(": not available\n");
	}
	else if (errorcode == 126)
	{
		_printp(data->name_progr);
		_printp(": ");
		_printp(n_as_string);
		_printp(": ");
		_printp(data->command_in);
		_printp(": Access denied\n");
	}
	return (0);
}
