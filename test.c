#include "shell.h"

/**
 * get_user_input - Reads a line of user input from a specefied stream
 * @command: a character array to strore the user input
 * @max_length: The max length of the input to read
 * @input_stream: the input stream to read from
 * Return: 0 if an error occur during input reading
 */
int get_user_input(char command[], size_t max_length, FILE *input_stream)
{
	size_t line_length;

	line_length = getline(&command, &max_length, input_stream);

	if (line_length == (size_t)-1)
	{
		if (feof(input_stream))
		{
			return (0);
		}
		else
		{
			perror("getline");
			exit(1);
		}
	}
	if (command[line_length - 1] == '\n')
	{
		command[line_length - 1] = '\0';
	}
	return (1);
}
/**
 * is_valid_command - check if a given command is a valid executable
 * @command: The command to check
 *
 * Return: 1 if the command s valide executable, 0 Otherwise
 */
int is_valid_command(char command[])
{
	return (access(command, X_OK) == 0);
}
/**
 * fork_and_execute_command - forks a childs process and execute comand
 * @command: The command to be executed
 * @last_exit_status: pointer to store the exit status
 * Return: void
 */
void fork_and_execute_command(char command[], int *last_exit_status)
{
	int status;
	char *args[MAX_ARGS];
	int num_args = tokenize_command(command, args);

	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	else if (child_pid == 0)
	{
		if (num_args >= 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("execvp");
				exit(1);
			}
		}
			else
			{
				fprintf(stderr, "./hsh: Invalid command\n");
				exit(1);
			}
	}
			else
			{
				wait(&status);
			if (WIFEXITED(status))
			{
				*last_exit_status = WEXITSTATUS(status);
			}
		}
}



/**
 * parse_arguments - parses a string into an array of arguments
 * @input: The input string to be parced
 * @args: an array to store the parced arguments
 * Return: void
 */
void parse_arguments(char input[], char *args[])
{
	int arg_count = 0;

	args[0] = strtok(input, " ");
	while (args[arg_count] != NULL)
	{
		arg_count++;
		args[arg_count] = strtok(NULL, " ");
	}
}
