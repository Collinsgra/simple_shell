#include "shell.h"
/**
 * main - initializes the vars of program
 * @argc: number of values received
 * @argv: values received
 * @environs: number of values received from the command line
 * Return: 0 on success.
 */
int main(int argc, char *argv[], char *environs[])
{
	program_datas data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	init_datas(data, argc, argv, environs);

	signal(SIGINT, manage_prom);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = _PROMPT;
	}
	errno = 0;
	loop_prom(prompt, data);
	return (0);
}

/**
 * manage_prom - prints prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void manage_prom(int opr UNUSED)
{
	_print("\n");
	_print(_PROMPT);
}

/**
 * init_datas - initialize struct with information of program.
 * @data: ptr to struct data
 * @argv: arguments passed to the program run
 * @environs: environsiron pased to the program run
 * @argc: number of values received
 */
void init_datas(program_datas *data, int argc, char *argv[], char **environs)
{
	int i = 0;

	data->name_progr = argv[0];
	data->in_putln = NULL;
	data->command_in = NULL;
	data->executables_counts = 0;

	if (argc == 1)
		data->descrip = STDIN_FILENO;
	else
	{
		data->descrip = open(argv[1], O_RDONLY);
		if (data->descrip == -1)
		{
			_printp(data->name_progr);
			_printp(": 0: Can't Access ");
			_printp(argv[1]);
			_printp("\n");
			exit(127);
		}
	}
	data->toks = NULL;
	data->environs = malloc(sizeof(char *) * 50);
	if (environs)
	{
		for (; environs[i]; i++)
		{
			data->environs[i] = string_dup(environs[i]);
		}
	}
	data->environs[i] = NULL;
	environs = data->environs;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * loop_prom - infinite loop showing prompt
 * @data: infinite data that shows the prompt
 * @prompt: prompt
 * 
 */
void loop_prom(char *prompt, program_datas *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->executables_counts))
	{
		_print(prompt);
		error_code = string_len = _function(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			xpand_subs(data);
			xpand_vars(data);
			_tokenizer(data);
			if (data->toks[0])
			{ 
				error_code = run(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
