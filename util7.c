
#include "shell.h"


/**
* help_alias - Displays information on the shell by builtin command 'alias'
*/
void help_alias(void)
{
char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

write(STDOUT_FILENO, msg, str_len(msg));
msg = "\n\talias: Prints a list of all aliases, one per line, in ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
write(STDOUT_FILENO, msg, str_len(msg));
msg = " the aliases name, name2, etc. one per line, in the ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
write(STDOUT_FILENO, msg, str_len(msg));
msg = " an alias for each NAME whose VALUE is given. If NAME ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "is already an alias, replace its value with VALUE.\n";
write(STDOUT_FILENO, msg, str_len(msg));
}

/**
* help_cd - Displays information on the shell by builtin command 'cd'
*/
void help_cd(void)
{
char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

write(STDOUT_FILENO, msg, str_len(msg));
msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "command is interpreted as cd $HOME. If the argument '-' is";
write(STDOUT_FILENO, msg, str_len(msg));
msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "\tThe environment variables PWD and OLDPWD are updated ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "after a change of directory.\n";
write(STDOUT_FILENO, msg, str_len(msg));
}

/**
* help_exit - Displays information on the shell by builtin command 'exit'
*/
void help_exit(void)
{
char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

write(STDOUT_FILENO, msg, str_len(msg));
msg = "STATUS argument is the integer used to exit the shell.";
write(STDOUT_FILENO, msg, str_len(msg));
msg = " If no argument is given, the command is interpreted as";
write(STDOUT_FILENO, msg, str_len(msg));
msg = " exit 0.\n";
write(STDOUT_FILENO, msg, str_len(msg));
}

/**
* help_help - Displays information on the shell by builtin command 'help'
*/
void help_help(void)
{
char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

write(STDOUT_FILENO, msg, str_len(msg));
msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "builtin command.\n";
write(STDOUT_FILENO, msg, str_len(msg));
}


/**
* parse_inp_command - Parses the command recieved from stdin
* @input: String gathered from stdin
* Return: Parsed strings to be used as arguments
*/
char **parse_inp_command(char *input)
{
char **arguments;
char *argument;
int i = 0;
int buffsize = BUFFER;

if (input[0] == ' ' && input[str_len(input)] == ' ')
exit(0);

if (input == NULL)
return (NULL);

arguments = malloc(sizeof(char *) * buffsize);
if (!arguments)
{
free(arguments);
perror("hsh");
return (NULL);
}

argument = mystrtok(input, "\n\t\r\a ");
while (argument)
{
arguments[i] = argument;
argument = mystrtok(NULL, "\n\t\r\a ");
i++;
}

arguments[i] = NULL;
return (arguments);
}



