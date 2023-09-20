#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>

#define MAX_CMD_LENGTH 10254
#define MAX_ARGS 50
#define BUFFER_SIZE 1024
#define MAX_PATH_LENGTH 1024



/*shell.c*/
int main(int argc, char *argv[]);
/*tokenizer.c*/
void _split(const char *cmd_buffer, char delimiter, char **av, int max_tokens);
int tokenize_command(char command[], char *args[]);
/*environment*/
void print_environment_variables(void);
int set_environment_variable(const char *variable, const char *value);
int unset_environment_variable(const char *variable);
/*cd.c*/
void update_pwd_variable(void);
/*test.c*/
int get_user_input(char command[], size_t max_length, FILE *input_stream);
int is_valid_command(char command[]);
void fork_and_execute_command(char command[], int *last_exit_status);
void parse_arguments(char input[], char *args[]);

void execute_piped_commands(const char *cmd1, const char *cmd2);
void execute_commands_in_pipe_and_wait_for_child_processes_to_finish(int *pipefd,
                                                                     pid_t pid1,
                                                                     pid_t pid2);
void fork_child_processes_and_create_pipe(int *pipefd, pid_t *pid1, pid_t *pid2);




/*test2.c*/
void trim_whitespace(char *str);
/*void execute_piped_commands(const char *cmd1, const char *cmd2);*/
/*runshell.c*/
void run_shell(FILE *input_stream);

#endif
