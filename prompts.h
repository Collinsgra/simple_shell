#ifndef ASSIST_H
#define ASSIST_H

/* Prompt */
#define _PROMPT "koch-cln$ "

/* Restart from the unused attibute */
#define UNUSED __attribute__((unused))

/* buffer size for each read call in _function */
#define BUFFER_SIZE 1024

/********* HELP BUILT IN **********/

#define HELP_DET_CD "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the shell working directory.\n"\
"	If there is no argument given to cd the command will get as interpreted\n"\
"	as cd $HOME.\n"\
"	if the argument help is - (cd -), the command will also be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_DET_EXIT "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple-shell.\n\n"\
"	Exits simple shell with a status of N.  If N is omitted, the exit status\n"\
"	is that of the last command runned.\n\n"

#define HELP_DET_ENV "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will be printed as a  complete list of enviroment variables.\n\n"

#define HELP_DET_SETENV "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	initialize a new environment variable\n"\
"	When there are not correct numbers of the arguments it print error message.\n\n"

#define HELP_DET_UNSETENV "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one of the variable from the environment.\n\n"\
"	When there are not correct numbers of the arguments it print error message.\n\n"

#define HELP_DET "help=\n"\
"help:\thelp [BUILTIN_HELP]\n\n"\
"	Displays info of builtin commands.\n\n"\
"	Displays summaris of builtin commands.  If BUILTIN_HELP is\n"\
"	specified, gives detailed to help on all comm matching BUILTIN_HELP,\n"\
"	otherwise list of help to be printed BUILTIN_HELP list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_HELP specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
