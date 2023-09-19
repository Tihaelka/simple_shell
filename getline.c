#include "shell.h"
/**
 * _getline - Read a line from a file stream.
 * @lineptr: A pointer to buffer that will store the line.
 * @stream: The file stream to read from.
 *
 * Return: The number of tha caracter reads in the line
 */
ssize_t _getline(char **lineptr, FILE *stream)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	size_t line_length = 0;
	ssize_t c;

	*lineptr = NULL;

	while ((c = getc(stream)) != EOF)
	{
		if (c == '\n')
		{
			break;
		}
	if (buffer_size == 0)
	{
		buffer_size = BUFFER_SIZE;
		buffer = malloc(buffer_size * sizeof(char));
		if (buffer == NULL)
		{
			return (-1);
		}
	}
	buffer[line_length++] = c;

	if (line_length == buffer_size)
	{
		buffer_size *= 2;
		buffer = realloc(buffer, buffer_size * sizeof(char));
		free(buffer);
		return (-1);
	}
	}
	if (line_length == 0)
	{
		return (-1);
	}
	*lineptr = buffer;
	(*lineptr)[line_length] = '\0';

	return (line_length);
}
