#include "shell.h"
/**
 * run_shell_from_file - Executes shell commands from a file.
 * @filename: The name of the file containing shell commands
 *
 * Return: void
 */
void run_shell_from_file(const char *filename)
{
	FILE *file_input_stream = fopen(filename, "r");

	if (file_input_stream == NULL)
	{
		perror("Failed to open the file");
		return;
	}
	run_shell(file_input_stream);

	fclose(file_input_stream);
}
