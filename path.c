#include "shell.h"
/**
 * execute_command - execute a command by searching for it in the path.
 * @command: The name of the command to execute.
 *
 * Return: void
 */
void execute_command(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char full_path[MAX_CMD_LENGTH];

		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				execl(full_path, command, NULL);
				perror("execl");
				exit(EXIT_FAILURE);
			}
			else
			{
				int status;

				waitpid(pid, &status, 0);
				return;
			}
		}
		token = strtok(NULL, ":");
	}
	printf("command not found: %s\n", command);
	free(path_copy);
}
/**
 * trim_whitespace - Removes leading and trealing whitespaces from a string
 * @str: the string to be trimmed
 *
 * Return: void
 */
void trim_whitespace(char *str)
{
	char *end;

	while (isspace(*str))
	{
		str++;
	}
	if (*str == 0)
	{
		return;
	}
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
	{
		end--;
	}
	end[1] = '\0';
}

