#include "shell.h"
/**
 * _split - It takes a command buffer as a input
 * and split it into tokens, storing them in array
 * @cmd_buffer: The input string to be split
 * @delimiter: The character use to delimit the token
 * @av: An array will the token be sorted
 * @max_tokens: The max number of tokens
 */
void _split(char *cmd_buffer, char delimiter, char **av, int max_tokens)
{
	char *token;
	int i;

	token = strtok(cmd_buffer, &delimiter);
	i = 0;

	while (token != NULL && i < max_tokens)
	{
		av[i] = token;
		token = strtok(NULL, &delimiter);
		i++;
	}
}
