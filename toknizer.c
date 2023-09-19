#include "shell.h"

/**
 * _split - Splits a string into tokens using a specified delimiter
 * @cmd_buffer: The input string to be split
 * @delimiter: caractere used to spit string
 * @av: Array to store the resulting tokens
 * @max_tokens: max numbers of tokens to split the string into
 *
 * Return: void
 */
void _split(const char *cmd_buffer, char delimiter, char **av, int max_tokens)
{
	const char *start = cmd_buffer;
	int i = 0;

	while (*cmd_buffer && i < max_tokens - 1)
	{
		if (*cmd_buffer == delimiter)
		{
			av[i++] = strndup(start, cmd_buffer - start);
			start = cmd_buffer + 1;
		}
		cmd_buffer++;
	}
	av[i++] = strdup(start);
	while (i < max_tokens)
	{
		av[i++] = NULL;
	}
}
/**
 * tokenize_command - Tokenizes a command string into arguments
 * @command: The command string to be Tokenized
 * @args: An array to strore the tokenized arguments
 *
 * Return: The number of arguments tokenized
 */
int tokenize_command(char command[], char *args[])
{
	int num_args = 0;
	char *token = strtok(command, " ");

	while (token != NULL && num_args < MAX_ARGS - 1)
	{
		args[num_args++] = token;
		token = strtok(NULL, " ");
	}

	args[num_args] = NULL;
	return (num_args);
}
