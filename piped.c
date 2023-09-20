#include "shell.h"
void fork_child_processes_and_create_pipe(int *pipefd, pid_t *pid1, pid_t *pid2) {
  if (pipe(pipefd) == -1) {
    perror("pipe");
    return;
  }

  *pid1 = fork();
  if (*pid1 == -1) {
    perror("fork");
    return;
  }

  if (*pid1 == 0) {
    close(pipefd[0]);
    return;
  }

  *pid2 = fork();
  if (*pid2 == -1) {
    perror("fork");
    return;
  }

  if (*pid2 == 0) {
    close(pipefd[1]);
    return;
  }
}

void execute_commands_in_pipe_and_wait_for_child_processes_to_finish(int *pipefd,
                                                                     pid_t pid1,
                                                                     pid_t pid2) {
  close(pipefd[0]);
  close(pipefd[1]);

  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
}

void execute_piped_commands(const char *cmd1, const char *cmd2) {
  int pipefd[2];
  pid_t pid1, pid2;

  fork_child_processes_and_create_pipe(pipefd, &pid1, &pid2);

  if (pid1 == 0) {
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    execlp("/bin/sh", "/bin/sh", "-c", cmd1, NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
  } else if (pid2 == 0) {
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    execlp("/bin/sh", "/bin/sh", "-c", cmd2, NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
  } else {
    execute_commands_in_pipe_and_wait_for_child_processes_to_finish(pipefd, pid1,
                                                                     pid2);
  }
}

