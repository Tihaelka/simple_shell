#include "shell.h"

/**
 * set_environment_variable - set environment variable to a specefied value
 * @variable: the name of the environment variable
 * @value: the set value of the environment variable
 * Return: 0 on success, -1 otherwise
 */
int set_environment_variable(const char *variable, const char *value)
{
	if (setenv(variable, value, 1) != 0)
	{
		fprintf(stderr, "Error: Unable to set environment variable.\n");
		return (1);
	}
	return (0);
}

/**
 * unset_environment_variable - remove an environment variable
 * @variable: the name of the environment variable
 *
 * Return: 0 on success, -1 otherwise
 */
int unset_environment_variable(const char *variable)
{
	if (unsetenv(variable) != 0)
	{
		fprintf(stderr, "Error: Unable to set environment variable.\n");
		return (1);
	}
	return (0);
}

/**
 * print_environment_variables - print environment variable
 *
 * Return: void
 */
void print_environment_variables()
{
	extern char **environ;
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}
