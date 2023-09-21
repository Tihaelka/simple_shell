#include "shell.h"
/**
 * main - Entry point
 * Return: no return
 */
int main(void)
{
	char *usr_int = NULL;
	int interactive = isatty(STDIN_FILENO);
	ssize_t rd;
	size_t int_size;
	char *cmd;
	pid_t child_pid;
	int last_sts, do_print, do_exec;
	char *cmd_cp;
	char *last_tok;
	char *var;

	while (1)
	{
		if (interactive)
		{
			printf("$ ");
		}

		int_size = 0;
		rd = getline(&usr_int, &int_size, stdin);

		if (rd == -1)
		{
			if (interactive)
			{
				printf("\n");
			}
			if (feof(stdin))
			{
				free(usr_int);
				return (0);
			}
			else
			{
				perror("getline");
				free(usr_int);
				exit(1);
			}
		}

		usr_int[strcspn(usr_int, "\n")] = '\0';
		cmd_cp = strdup(usr_int);
		last_tok = NULL;

		cmd = strtok_r(cmd_cp, ";", &last_tok);
		last_sts = 0;
		do_print = 0;

		while (cmd != NULL)
		{
			do_exec = 1;

			if (strstr(cmd, "&&"))
			{
				do_exec = (last_sts == 0);
			}
			else if (strstr(cmd, "||"))
			{
				do_exec = (last_sts != 0);
			}
			if (do_exec)
			{
				var = strstr(cmd, "$");
				if (var)
				{
					char var_name[64];

					sscanf(var, "$%63s", var_name);

					if (strcmp(var_name, "?") == 0)
					{
						sprintf(var, "%d", last_sts);
					}
					else if (strcmp(var_name, "$") == 0)
					{
						sprintf(var, "%d", getpid());
					}
				}

				child_pid = fork();

				if (child_pid == -1)
				{
					perror("fork");
					free(usr_int);
					free(cmd_cp);
					exit(1);
				}
				else if (child_pid == 0)
				{
					char *args[4];
					args[0] = "sh";
					args[1] = "-c";
					args[2] = cmd;
					args[3] = NULL;

					execvp("sh", args);
					perror("execvp");
					exit(127);
				}
				else
				{
					int status;
					waitpid(child_pid, &status, 0);
					last_sts = WEXITSTATUS(status);
					do_print = 1;
				}
			}
			cmd = strtok_r(NULL, ";", &last_tok);
		}
		if (do_print && interactive && last_sts != 0)
		{
			printf("%d\n",last_sts);
		}
		if (strcmp(usr_int, "exit") == 0)
		{
			free(usr_int);
			free(cmd_cp);
			return (0);
		}
		free(usr_int);
		free(cmd_cp);
		usr_int = NULL;
		cmd_cp = NULL;
	}
	return (0);
}
