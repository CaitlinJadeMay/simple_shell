#include "shell.h"


/**
* history_dis - display history of user input on simple_shell
* @c: parsed command
* @st: status of last command executed
* Return: 0 success or -1 if fail
*/
int history_dis(__attribute__((unused))char **c, __attribute__((unused))int st)
{
char *filename = ".simple_shell_history";
FILE *fp;
char *line = NULL;
size_t len = 0;
int counter = 0;
char *er;

fp = fopen(filename, "r");
if (fp == NULL)
{
return (-1);
}
while ((getline(&line, &len, fp)) != -1)
{
counter++;
er = myitoa(counter);
MYPRINT(er);
free(er);
MYPRINT(" ");
MYPRINT(line);
}
if (line)
free(line);
fclose(fp);
return (0);
}

/**
* check_builtin - Checks if parsed command in built-in
* @cmd: Parsed command to be check
* Return: 0 Succes -1 Fail
*/
int check_builtin(char **cmd)
{
builtin fun[] = {
{"cd", NULL},
{"help", NULL},
{"echo", NULL},
{"env", NULL},
{"history", NULL},
{NULL, NULL}
};
int i = 0;

if (*cmd == NULL)
{
return (-1);
}
while ((fun + i)->command)
{
if (mystrcmp(cmd[0], (fun + i)->command) == 0)
return (0);
i++;
}
return (-1);
}

/**
* builtin_cmd - Handles predefined built in commands
* @cmd: Array of parsed command strings
* @st: Status of last execution
* Return: -1 Failure 0 Success
*/
int builtin_cmd(char **cmd, int st)
{
builtin built_in[] = {
{"cd", change_dir},
{"env", dis_env},
{"help", display_help},
{"echo", echo_bul},
{"history", history_dis},
{NULL, NULL}
};
int i = 0;

for (i = 0; (built_in + i)->command != NULL; i++)
{
if (mystrcmp(cmd[0], (built_in + i)->command) == 0)
{
return ((built_in + i)->function(cmd, st));
}
}

return (-1);
}


/**
* exit_built_in_stat - Exit Status for built-in commands
* @cmd: Array of parsed command strings
* @input: Input recieved from user (to be freed)
* @argv: Arguments before program starts(argv[0] == Shell Program Name)
* @c: Shell execution count
* @stat: Exit status
*/
void exit_built_in_stat(char **cmd, char *input, char **argv, int c, int stat)
{
int status, i = 0;

if (cmd[1] == NULL)
{
free(input);
free(cmd);
exit(stat);
}

for (i = 0; cmd[1][i]; i++)
{
if (myisalpha(cmd[1][i]) != 0)
{
myprerror(argv, c, cmd);
free(input);
free(cmd);
exit(2);
}
else
{
status = myatoi(cmd[1]);
if (status == 2)
{
myprerror(argv, c, cmd);
free(input);
free(cmd);
exit(status);
}
free(input);
free(cmd);
exit(status);
}
}
}


