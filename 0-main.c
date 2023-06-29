#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
char *buffer;
size_t bufsize = BUFFER_SIZE;
ssize_t lineSize;
pid_t pid;
if(argc < 1)
{
perror("Please enter at least 1 argument\n");
exit(EXIT_FAILURE);
}
buffer = (char *)malloc(bufsize * sizeof(char));
if (buffer == NULL) {
perror("Allocation error");
exit(EXIT_FAILURE);
}

while (1) {
printf("($) ");
lineSize = getline(&buffer, &bufsize, stdin);
if (lineSize == -1) {
if (feof(stdin)) {
printf("\n");
break;  /* Exit the loop on EOF (Ctrl+D) */
} else {
perror("Read error");
exit(EXIT_FAILURE);
}
}

/* Remove the trailing newline character */
buffer[strcspn(buffer, "\n")] = '\0';

/* Fork a child process */
pid = fork();

if (pid == -1) {
perror("Fork error");
exit(EXIT_FAILURE);
} else if (pid == 0) {
/* Child process */

/* Tokenize the command and arguments */
char *args[2];  /* Maximum number of arguments is 1 */
args[0] = buffer;
args[1] = NULL;

/* Execute the command */
if (execve(args[0], args, NULL) == -1) {
fprintf(stderr, "%s: No such file or directory\n", argv[0]);
exit(EXIT_FAILURE);
}

exit(EXIT_SUCCESS);
} else {
/* Parent process */
int status;
wait(&status);
}
}

free(buffer);
return 0;
}

