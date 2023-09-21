#include "shell.h"
/**
 * my_setenv - sets an environment variable
 * @shell_name: the name of the shell
 * @av: array of strings containing command line
 * arguments
 * Return: no return
 */
void my_setenv(char *shell_name, char **av)
{
	char *varname;
	char *value;
	char *old_value;

	if (av[1] == NULL || av[2] == NULL)
	{
		fprintf(stderr, "%s: Missing variable name or value.\n",
				shell_name);
		return;
	}
	varname = av[1];
	value = av[2];
	old_value = getenv(varname);

	if (setenv(varname, value, old_value ? 1 : 0) != 0)
	{
		fprintf(stderr, "%s: Failed to set environment variable.\n",
				shell_name);
	}
}
/**
 * my_unsetenv - unset an environment variable
 * @shell_name: the name of the shell
 * @av: array of strings containing command line arguments
 * Return: no return
 */
void my_unsetenv(char *shell_name, char **av)
{
	int length;
	int i;
	int j;

	if (!av[1])
	{
		fprintf(stderr, "%s: Variable name not given.\n",
				shell_name);
		return;
	}
	if (getenv(av[1]) == NULL)
	{
		fprintf(stderr, "%s: Variable not found.\n",
				shell_name);
		return;
	}
	length = strlen(av[1]);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], av[1], length) == 0
				&& environ[i][length] == '=')
		{
			for (j = i; environ[j]; j++)
			{
				environ[j] = environ[j + 1];
			}
			break;
		}
	}
}

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
