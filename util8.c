
#include "shell.h"


/**
* print_error - Displays error message
* @input: Input recieved from user
* @counter: Count of shell loop
* @argv: Arguments before program starts(argv[0] == Shell Program Name)
*/

void print_error(char *input, int counter, char **argv)
{
char *er;

MYPRINT(argv[0]);
MYPRINT(": ");
er = myitoa(counter);
MYPRINT(er);
free(er);
MYPRINT(": ");
MYPRINT(input);
MYPRINT(": not found\n");
}

/**
*  myprerror - Prints custom Error
* @argv: Arguments before program starts(argv[0] == Shell Program Name)
* @c: Error Count
* @cmd: Array of parsed command strings
*/

void myprerror(char **argv, int c, char **cmd)
{
char *error = myitoa(c);

MYPRINT(argv[0]);
MYPRINT(": ");
MYPRINT(error);
MYPRINT(": ");
MYPRINT(cmd[0]);
MYPRINT(": Illegal number: ");
MYPRINT(cmd[1]);
MYPRINT("\n");
free(error);
}

/**
* custom_error_file - Prints custom Error
* @argv: Arguments before program starts(argv[0] == Shell Program Name)
* @c: Error Count
*/
void custom_error_file(char **argv, int c)
{
char *er = myitoa(c);

MYPRINT(argv[0]);
MYPRINT(": ");
MYPRINT(er);
MYPRINT(": Can't open ");
MYPRINT(argv[1]);
MYPRINT("\n");
free(er);
}


/**
* signal_to_handle - Configures ^C not to terminate our shell
* @sig: Incoming Signal
*/
void signal_to_handle(int sig)
{
if (sig == SIGINT)
{
MYPRINT("\n$ ");
}
}



/**
* execute_echo_command - Executes built-in echo function
* @cmd: Parsed Command
* Return: 0 Upon Success -1 Upon Failure
*/
int execute_echo_command(char **arguments)
{
pid_t process_id;
int status;

process_id = fork();
if (process_id == 0)
{
if (execve("/bin/echo", arguments, environ) == -1)
{
return (-1);
}
exit(EXIT_FAILURE);
}
else if (process_id < 0)
{
return (-1);
}
else
{
do {
waitpid(process_id, &status, WUNTRACED);
} while (!(WIFEXITED(status) || WIFSIGNALED(status)));
}

return (1);
}


