#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

#define MAX_CMD_LENGTH 100
#define MAX_TOKENS  10
#define BUFFER_SIZE 1024

extern char **environ;

/**
 * struct data - struct to hold command data
 * @av: array of command tokens
 * @last_exit: stores the exit status of the last
 * command
 */
struct data
{
	char *av[MAX_TOKENS];
	int last_exit;
};
/*user.c*/
void get_user_input(char *user_input, size_t max_length);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
/*split.c*/
void _split(char *cmd_buffer, char delimiter, char **av, int max_tokens);
/*command.c*/
void exec_cmd(struct data *c);
/*exit.c*/
void exit_status(int exit_code, char *av[]);
int is_exit_command(const char *command);

/*runshell.c*/
int main(void);

/*helpers.c*/
void process_command(const char *command, int interactive);
void execute_command(const char *command);

/*environment.c*/
void my_setenv(char *shell_name, char **av);
void my_unsetenv(char *shell_name, char **av);
void execute_env_builtin(void);

#endif
