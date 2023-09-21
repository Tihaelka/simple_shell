#include "shell.h"

int is_exit_command(const char *command)
{
	return (strcmp(command, "exit") == 0);
}

void process_command(const char *command, int interactive)
{
	if (is_exit_command(command))
	{
		if (interactive)
		{
			printf("./hsh: No such file or directory\n");
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
			printf("./hsh: no such file or directory\n");
		}
	}
}
void execute_command(const char *command)
{
	pid_t child_pid;
	char *path;
	char *dir;

	child_pid = fork();
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

