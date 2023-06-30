#include "shell.h"


/**
* main - Entry point of program
* @argc: Argument count
* @argv: Argument vector
* Return: Returns condition
*/
int main(__attribute__((unused)) int argc, char **argv)
{
char *user_input, **command, **command_list;
int command_count = 0, index, loop_condition = 1, status = 0;
if (argv[1] != NULL)
read_file(argv[1], argv);
signal(SIGINT, signal_to_handle);
while (loop_condition)
{
command_count++;
if (isatty(STDIN_FILENO))
MYPRINT("$ ");
user_input = mygetline();
if (user_input[0] == '\0')
continue;
simple_shell_history(user_input);
command_list = separate_by_semi_col(user_input);
index = 0;
while (command_list[index] != NULL)
{
command = parse_inp_command(command_list[index]);
if (mystrcmp(command[0], "exit") == 0)
{
free(command_list);
exit_built_in_stat(command, user_input, argv, command_count, status);
}
else if (check_builtin(command) == 0)
{
status = builtin_cmd(command, status);
free(command);
continue;
}
else
status = check_cmd(command, user_input, command_count, argv);
free(command);
index++;
}
free(user_input);
free(command_list);
wait(&status);
}
return (status);
}

