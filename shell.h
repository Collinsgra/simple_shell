#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USEgt_line 0
#define USE_STRTOK 0
#define HIST_FILE	".shell_history"
#define HIST_MAX	4096
extern char **environ;

/**
 * struct liststr - linked list
 * @num: number field
 * @str: a string
 * @next: points to next data
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - pointer function
 *@arg: a strgenerated
 *@argv: arrays str gene
 *@path: a string path for current command
 *@argc: arguments
 *@line_count: errors
 *@err_num: the error code for exit()s
 *@totalLns_cnt_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list of env 
 *@environ: ccopy of envir
 *@history: the history data
 *@alias: the alias data
 *@env_changed: change enviro
 *@status: return status
 *@cmd_buf: pointer
 *@command_typ_buffer: command type ||, &&, ;
 *@readfd: fd to read
 *@histcount: history
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int totalLns_cnt_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int command_typ_buffer;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtins
 *@type: builtins comm flags
 *@func: functions
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int builtin_checker_file(info_t *);
void find_a_command(info_t *);
void func_fork(info_t *);
int cmd_cln(info_t *, char *);
char *chars_clone(char *, int, int);
char *check_path(info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int string__length(char *);
int compare_string(char *, char *);
char *starts_with(const char *, const char *);
char *string_conc(char *, char *);
char *copy_string(char *, char *);
char *string_duplicate(const char *);
void _puts(char *);
int _putchar(char);
char *copy_str(char *, char *, int);
char *conc_str(char *, char *, int);
char *chars_str(char *, char);
char **string_to_words(char *, char *);
char **string_to_words2(char *, char);
char *setMemory(char *, char, unsigned int);
void free_str_str(char **);
void *_realloc(void *, unsigned int, unsigned int);
int free_ptr(void **);
int reciprocal(info_t *);
int limiter_de_fe(char, char *);
int _isalpha(int);
int _atoi(char *);
int error_asc(char *);
void print_error(info_t *, char *);
int printDal(int, int);
char *changeNum(long int, int, int);
void deleteComments(char *);
int _shellexit(info_t *);
int _shellcd(info_t *);
int _shellhelp(info_t *);
int shellHistory(info_t *);
int shellAlias(info_t *);
ssize_t gt_inpuutt(info_t *);
int gt_line(info_t *, char **, size_t *);
void ctrl_Handle(int);
void wipeInfo(info_t *);
void makeInformation(info_t *, char **);
void allow_info(info_t *, int);
char *gt_environ(info_t *, const char *);
int shellenv(info_t *);
int shellsetenv(info_t *);
int shellunsetenv(info_t *);
int multiply_list_of_env(info_t *);
char **get_environ(info_t *);
int unset_environ(info_t *, char *);
int set_environ(info_t *, char *, char *);
char *retr_history_doc(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int make_list_of_history(info_t *info, char *buf, int totalLns_cnt);
int reshuffle_hist(info_t *info);
list_t *add_data(list_t **, const char *, int);
list_t *add_poss_end(list_t **, const char *, int);
size_t string_prt_st(const list_t *);
int remove_data(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **stringList(list_t *);
size_t listPrinted(const list_t *);
list_t *dt_begins_at(list_t *, char *, char);
ssize_t receiveData(list_t *, list_t *);
int equal_to_chain(info_t *, char *, size_t *);
void _checker(info_t *, char *, size_t *, size_t, size_t);
int alias_displace(info_t *);
int rep_variables(info_t *);
int str_rep(char **, char *);

#endif
