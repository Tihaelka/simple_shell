#include "main.h"
/**
 * custom_getline - Reads a line from a file stream into
 * a buffer
 * @lineptr: pointer to a pointer that holds the address of the
 * buffer allocated
 * @n: pointer to a variable that holds the size of the buffer
 * @stream: the file stream to read the line from
 * Return: return the line length on success, -1 if it failed
 */
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
