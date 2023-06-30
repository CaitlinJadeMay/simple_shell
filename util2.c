#include "shell.h"


/**
* check_cmd - Excutes commands found in predefined path
* @cmd: Array of parsed command strings
* @input: Input recieved from user (to be freed)
* @c:Shell Excution Time Case of Command Not Found
* @argv: Arguments before program starts(argv[0] == Shell Program Name)
* Return: 1 Case Command Null -1 Wrong Command 0 Command Excuted
*/
int check_cmd(char **cmd, char *input, int c, char **argv)
{
int wstatus;
pid_t pid;

if (*cmd == NULL)
return (EXIT_FAILURE);
pid = fork();
if (pid == -1)
{
perror("Error");
return (-1);
}
if (pid == 0)
{
if (mystrncmp(*cmd, "./", 2) != 0 && mystrncmp(*cmd, "/", 1) != 0)
find_command_path(cmd);
if (access(cmd[0], R_OK) != 0)
{
print_error(cmd[0], c, argv);
free(cmd);
free(input);
cmd = NULL;
input = NULL;
exit(127);
}
if (execve(*cmd, cmd, environ) == -1)
return (2);
else
return (0);
}
wait(&wstatus);
if (WIFEXITED(wstatus))
{
if (WEXITSTATUS(wstatus) == 0)
return (0);
else if (WEXITSTATUS(wstatus) == 2)
return (2);
else if (WEXITSTATUS(wstatus) == 127)
return (127);
}
return (127);
}

/**
* read_file - Reads commands from the argument File
* @file: File containing commands
* @argv: Arguments passed
* Return: -1 or 0
*/
void read_file(char *file, char **argv)
{
FILE *fp;
char *line = NULL;
size_t len = 0;
int count = 0;

fp = fopen(file, "r");
if (fp == NULL)
{
custom_error_file(argv, count);
exit(127);
}
while (getline(&line, &len, fp) != -1)
{
count++;
parse_commands(line, count, fp, argv);
}

if (line)
free(line);

fclose(fp);
exit(0);
}


/**
* parse_commands - Parse commands and handle their execution
* @line: Line from file
* @count: Error counter
* @fp: File descriptor
* @argv: Command line arguments
*/
void parse_commands(char *line, int count, FILE *fp, char **argv)
{
char **command;
int status = 0;

command = parse_inp_command(line);
if (mystrncmp(command[0], "exit", 4) == 0)
check_exit_status(command, line, fp);
else if (check_builtin(command) == 0)
{
status = builtin_cmd(command, status);
free(command);
}
else
{
status = check_cmd(command, line, count, argv);
free(command);
}
}

/**
* check_exit_status - Exit status handler for file input
* @line: Line from a file
* @cmd: Parsed command
* @fd: File Descriptor
*/
void check_exit_status(char **cmd, char *line, FILE *fd)
{
int status;
int i = 0;

if (cmd[i] == NULL)
{
free(line);
free(cmd);
fclose(fd);
exit(errno);
}

while (cmd[1][i])
{
if (myisalpha(cmd[1][i++]) < 0)
perror("Illegal number");
}

status = myatoi(cmd[1]);
free(line);
free(cmd);
fclose(fd);
exit(status);
}

