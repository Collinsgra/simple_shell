#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include "prompts.h"

/**
 * struct data_s - struct for the program's data
 * @name_progr: the nameof executable
 * @in_putln: ptr to input read for _function
 * @command_in: first command typed in the commandline
 * @executables_counts: number of comands excecuted
 * @descrip: description to the command's input
 * @toks: tokens
 * @environs: environ's copy
 * @lists_one: arrays ptrs with subs.s
 */
typedef struct data_s
{
	char *name_progr;
	char *in_putln;
	char *command_in;
	int executables_counts;
	int descrip;
	char **toks;
	char **environs;
	char **alias_list;
} program_datas;


/**
 * struct _builtins - structure for builtins
 * @builtin: name of builtin
 * @function: function for builtins
 */
typedef struct _builtins
{
	char *builtins;
	int (*function)(program_datas *data);
} _builtins;

void init_datas(program_datas *data, int arc, char *argv[], char **environs);

/* infinite loop showing prompt*/
void loop_prom(char *prompt, program_datas *data);

/* Print prompt in newline */
void manage_prom(int opr UNUSED);

int _function(program_datas *data);

int check_logic_ops(char *array_commands[], int i, char array_operators[]);

void xpand_vars(program_datas *data);

/* substitute  xpands */
void xpand_subs(program_datas *data);

int buffer_add(char *buffer, char *string_add);

void _tokenizer(program_datas *data);

char *str_tok(char *line, char *separ);

int run(program_datas *data);

int builtinlist(program_datas *data);

char **tokenize_path(program_datas *data);

int find_prog(program_datas *data);

void free_array_of_pointers(char **directories);

void free_recurrent_data(program_datas *data);

void free_all_data(program_datas *data);

int builtin_exit(program_datas *data);

int builtin_cd(program_datas *data);

int set_work_directory(program_datas *data, char *new_dir);

int builtin_help(program_datas *data);

int builtin_alias(program_datas *data);

int builtin_env(program_datas *data);

int builtin_set_env(program_datas *data);

int builtin_unset_env(program_datas *data);

char *environ_get_key(char *name, program_datas *data);

int environ_remove_key(char *key, program_datas *data);

void _pt_environs(program_datas *data);

int _print(char *string);

int _printp(char *string);

int _print_error(int errorcode, program_datas *data);

int string_length(char *string);

char *string_dup(char *string);


int string_compare(char *string1, char *string2, int number);


char *string_concat(char *string1, char *string2);

void string_rev(char *string);


void long_string(long number, char *string, int base);

int _atoi(char *s);


int count_chars(char *string, char *character);



int print_alias(program_datas *data, char *alias);

char *get_alias(program_datas *data, char *alias);

int set_alias(char *alias_string, program_datas *data);


#endif
