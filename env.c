#include "main.h"
#include <unistd.h>

/**
 * execute_env_builtin - prints the environment variables to
 * standard output
 * Return: no return
 */
void execute_env_builtin(void)
{
	char **env_ptr = environ;

	while (*env_ptr != NULL)
	{
		printf("%s\n", *env_ptr);
		env_ptr++;
	}
}
