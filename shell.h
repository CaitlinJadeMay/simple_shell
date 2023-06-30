#ifndef SHELL_H
#define SHELL_H

/***** MACROS *****/
#define BUFFER 8192
#define MYPRINT(ch) (write(STDERR_FILENO, ch, str_len(ch)))
#define DELIM " \n\a\t\r"

/*** STANDARD LIBS ***/
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


/******** STRING HANDLER FUNCTIONS **********/

int str_len(char *s);
int myputchar(char c);
int myatoi(char *s);
int mystrcmp(char *s1, char *s2);
int myisalpha(int c);
void array_reverse(char *arr, int len);
char *myitoa(unsigned int n);
char *mystrcat(char *dest, char *src);
int mystrncmp(const char *s1, const char *s2, size_t n);
char *mystrdup(char *str);

/****** MISCELLANEOUS AND INPUT FUNCTIONS *******/

char *mygetline(void);
char *remove_space(char *str);
void remove_after_hash(char *buff);
unsigned int match_char(char c, const char *str);
char *mystrtok(char *str, const char *delim);
int simple_shell_history(char *input);
char **separate_by_semi_col(char *input);

/****** FILE ARGUMENT HANDLER FUNCTIONS ******/

void read_file(char *file, char **argv);
void parse_commands(char *line, int count, FILE *fp, char **argv);
void check_exit_status(char **cmd, char *line, FILE *fd);

/****** PARSED ARGUMENT HANDLER FUNCTIONS *****/

char **parse_inp_command(char *input);
int check_cmd(char **cmd, char *input, int c, char **argv);
void signal_to_handle(int sig);

/******* ERROR HANDLERS ******/

void print_error(char *input, int counter, char **argv);
void myprerror(char **argv, int c, char **cmd);
void custom_error_file(char **argv, int c);

/****** ENVIRONMENT HANDLERS ******/

extern char **environ;


/****** PRINTING FUNCTIONS *****/

void print_number(unsigned int n);
void print_integer(int n);
int execute_echo_command(char **cmd);

/******* PATH FINDER *******/
char *build_path(char *token, char *value);
int find_command_path(char **cmd);
char *mygetenv(char *name);

/******* HELP HANDLERS *******/

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
int display_help(char **cmd, __attribute__((unused))int st);

/****** BUILTIN COMMAND HANDLERS AND EXECUTE ******/

int check_builtin(char **cmd);
int builtin_cmd(char **cmd, int st);
void exit_built_in_stat(char **cmd, char *input, char **argv, int c, int stat);
int change_dir(char **cmd, __attribute__((unused))int st);
int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int st);
int echo_bul(char **cmd, int st);
int history_dis(__attribute__((unused))char **c, __attribute__((unused)) int st);

/****** BUILT-IN COMMANDS STRUCT *****/

/**
 * struct _builtin - Defines a struct that conatins built-in commands
 * with their respective implementation functions
 * @command: - Built-in command
 * @function: - Pointer to custom functions that have
 * similar functionalities as the built-in commands
 */
typedef struct _builtin
{
	char *command;
	int (*function)(char **line, int st);
} builtin;

#endif /*SHELL_H*/


