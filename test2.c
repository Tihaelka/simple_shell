#include "shell.h"
/**
 * trim_whitespace - Removes leading and trealing whitespaces from a string
 * @str: the string to be trimmed
 *
 * Return: void
 */
void trim_whitespace(char *str)
{
	char *end;

	while(isspace(*str))
	{
		str++;
	}
	if (*str == 0)
	{
		return;
	}
	end = str + strlen(str) -1;
	while (end > str && isspace(*end))
	{
		end--;
	}
	end[1] = '\0';
}
/**
 * execute_pipd_commads - executes two commands in a piped
 * @cmd1: the first command
 * @cmd2: the second one
 *
 * Return: void
 */
void execute_piped_commands(const char *cmd1, const char *cmd2)
{
	int pipefd[2];
	pid_t pid1, pid2;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return;
	}
	pid1 = fork();

	if (pid1 == -1)
	{
		perror("fork");
		return;
	}
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execlp("/bin/sh", "/bin/sh", "-c", cmd1, NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		pid2 = fork();

		if (pid2 == -1)
		{
			perror("fork");
			return;
		}
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execlp("/bin/sh", "/bin/sh", "-c", cmd2, NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);

		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	}
}
