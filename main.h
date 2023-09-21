#ifndef MAIN_H
#define MAIN_H

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

void get_user_input(char *user_input, size_t max_length);
void _split(char *cmd_buffer, char delimiter, char **av, int max_tokens);
void exec_cmd(struct data *c);
void exit_status(int exit_code, char *av[]);



int main(void);

int is_exit_command(const char *command);
void process_command(const char *command, int interactive);
void execute_command(const char *command);

int wait(int *status);

void execute_env_builtin(void);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

char prevDir[1024];

int change_directory(const char *dir, char *pdir);

void my_setenv(char *shell_name, char **av);
void my_unsetenv(char *shell_name, char **av);

void *the_realloc(void *c, unsigned int o_size, unsigned int n_size);
char *the_memset(char *s, char c, unsigned int n);

int is_interactive(void);
void execute_command_with_operators(const char *command);

#endif
