#include "main.h"
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

	line_length = getline(&user_input, &max_length, stdin);
	if (line_length == (size_t) -1)
	{
		exit(0);
	}

	if (user_input[line_length - 1] == '\n')
	{
		user_input[line_length - 1] = '\0';
	}
}
