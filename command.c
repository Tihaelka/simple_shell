#include "main.h"
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
