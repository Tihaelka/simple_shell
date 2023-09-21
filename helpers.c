#include "shell.h"
/**
 * process_command - process a command, executing
 * apppropriate action based on the command.
 * @command: The command to process
 * @interactive: Flag indication if shell is in the interactive mode
 * Return: no return.
 */
void process_command(const char *command, int interactive)
{
	if (is_exit_command(command))
	{
		if (interactive)
		{
			printf("./shell: No such file or directory\n");
		}
		else
		{
			char *av[] = {"exit", NULL};

			exit_status(0, av);
		}
	}
	else if (command[0] == '/')
	{
		execute_command(command);
	}
	else
	{
		if (interactive)
		{
			printf("./shell: no such file or directory\n");
		}
	}
}
/**
 *  execute_command - Executes a command by creating
 *  new process and using execlp to execute
 *  @command: the command to execute.
 *  Return: no return
 */

void execute_command(const char *command)
{
	pid_t child_pid = fork();
	char *path;
	char *dir;

	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	else if (child_pid == 0)
	{
		path = getenv("PATH");
		dir = strtok(path, ":");
		while (dir != NULL)
		{
			char executable_path[MAX_CMD_LENGTH];

			snprintf(executable_path, sizeof(executable_path), "%s%s", dir, command);
			if (access(executable_path, X_OK) == 0)
			{
				if (execlp(executable_path, command, NULL) == -1)
				{
					perror("execl");
					exit(1);
				}
			}
			dir = strtok(NULL, ":");
		}
	fprintf(stderr, "command not found: %s\n", command);
	exit(127);
	}
	else
	{
		int status;

		wait(&status);
	}
}
/**
 * exec_cmd - executes a command using the exexvp syscall
 * @c: a pointer to a data structure that contains the command
 * and its arguments' information
 * Return: no return
 */
void exec_cmd(struct data *c)
{
	char *cmd;
	char *args[MAX_TOKENS];
	int i;

	cmd = c->av[0];
	args[0] = cmd;

	for (i = 1; i < MAX_TOKENS; i++)
	{
		args[i] = c->av[i];
	}
	execvp(cmd, args);
	perror("execvp");
	exit(1);
}
