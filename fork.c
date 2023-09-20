#include "shell.h"
/**
 * fork_pipe - create a pipe and fork twho child process
 * @pipefd: pointer to an integer array to store pipe file description
 * @pid1: pointer to PID process variable for the first child process
 * @pid2: pointer to PID process variable for the second child process
 * return: void
 */
void fork_pipe(int *pipefd, pid_t *pid1, pid_t *pid2)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return;
	}
	*pid1 = fork();
	if (*pid1 == -1)
	{
		perror("fork");
		return;
	}
	if (*pid1 == 0)
	{
		close(pipefd[0]);
		return;
	}
	*pid2 = fork();
	if (*pid2 == -1)
	{
		perror("fork");
		return;
	}
	if (*pid2 == 0)
	{
		close(pipefd[1]);
		return;
	}
}
/**
 * exec_pipe - Execute command in a pipe
 * and wait for the child process to finish
 * @pipefd: pointer to an integer array to store pipe file description
 * @pid1: PID for the first child process
 * @pid2: PID for the second child process
 * return: void
 */
void exec_pipe(int *pipefd, pid_t pid1, pid_t pid2)
{
	close(pipefd[0]);
	close(pipefd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
/**
 * exec_piped_commands - Execute two piped commands
 * @cmd1: the first command to execute
 * @cmd2: the second command to execute
 * return: void
 */
void exec_piped_commands(const char *cmd1, const char *cmd2)
{
	int pipedfd[2];

	pid_t pid1, pid2;

	fork_pipe(pipedfd, &pid1, &pid2);

	if (pid1 == 0)
	{
		dup2(pipedfd[1], STDOUT_FILENO);
		close(pipedfd[1]);
		execlp("/bin/sh", "/bin/sh", "-c", cmd1, NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else if (pid2 == 0)
	{
		dup2(pipedfd[0], STDOUT_FILENO);
		close(pipedfd[0]);
		execlp("/bin/sh", "/bin/sh", "-c", cmd2, NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		exec_pipe(pipedfd, pid1, pid2);
	}
}
