#include "shell.h"
/**
 * main - Entry point
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Always 0 on success
 */
int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		run_shell(stdin);
	}
	else if (argc == 2)
	{
		FILE *input_stream = fopen(argv[1], "r");

		if (input_stream == NULL)
		{
			perror("fopen");
			return (1);
		}
		run_shell(input_stream);
		fclose(input_stream);
	}
	else
	{
		fprintf(stderr, "usage: %s [input_file]\n", argv[0]);
		return (1);
	}
	run_shell(stdin);
	return (0);
}
