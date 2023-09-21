#include "shell.h"

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_pos;
	static size_t buffer_size;

	size_t i;
	size_t line_length;

	if (buffer_pos >= buffer_size)
	{
		buffer_size = fread(buffer, 1, BUFFER_SIZE,
				stream);
		buffer_pos = 0;
		if (buffer_size == 0)
		{
			return (-1);
		}
	}
	i = buffer_pos;

	while (i < buffer_size && buffer[i] != '\n')
	{
		i++;
	}
	line_length = i - buffer_pos;
	if (*n < line_length + 1)
	{
		*n = line_length + 1;
		*lineptr = (char *)malloc(*n);
	}

	memcpy(*lineptr, buffer + buffer_pos, line_length);
	(*lineptr)[line_length] = '\0';

	buffer_pos = i + 1;
	return (line_length);
}

/**
 * get_user_input - obtains the user input form the command
 * line
 * @user_input: a pointer to a character buffer
 * @max_length: the maximum length of the input that can be
 * read
 * Return: no return
 */
void get_user_input(char *user_input, size_t max_length)
{
	size_t line_length;

	line_length = custom_getline(&user_input, &max_length, stdin);
	if (line_length == (size_t) -1)
	{
		exit(0);
	}

	if (user_input[line_length - 1] == '\n')
	{
		user_input[line_length - 1] = '\0';
	}
}

