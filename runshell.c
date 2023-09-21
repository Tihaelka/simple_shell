#include "shell.h"

int main(void) {
  char *cmd = NULL;
  size_t cmd_size = 0;
  pid_t child_pid;
  int last_sts, do_print, do_exec;
  char *cmd_cp;
  char *last_tok;
  char *var;

  while (1) {
    printf("$ ");

    getline(&cmd, &cmd_size, stdin);

    if (cmd == NULL) {
      if (feof(stdin)) {
        return 0;
      } else {
        perror("getline");
        exit(1);
      }
    }

    cmd[strcspn(cmd, "\n")] = '\0';
    cmd_cp = strdup(cmd);
    last_tok = NULL;

    cmd = strtok_r(cmd_cp, ";", &last_tok);
    last_sts = 0;
    do_print = 0;

    while (cmd != NULL) {
      do_exec = 1;

      if (strstr(cmd, "&&")) {
        do_exec = (last_sts == 0);
      } else if (strstr(cmd, "||")) {
        do_exec = (last_sts != 0);
      }

      if (do_exec) {
        var = strstr(cmd, "$");
        if (var) {
          char var_name[64];

          sscanf(var, "$%63s", var_name);

          if (strcmp(var_name, "?") == 0) {
            sprintf(var, "%d", last_sts);
          } else if (strcmp(var_name, "$") == 0) {
            sprintf(var, "%d", getpid());
          }
        }

        child_pid = fork();

        if (child_pid == -1) {
          perror("fork");
          free(cmd);
          free(cmd_cp);
          exit(1);
        } else if (child_pid == 0) {
          char *args[4];
          args[0] = "sh";
          args[1] = "-c";
          args[2] = cmd;
          args[3] = NULL;

          execvp("sh", args);
          perror("execvp");
          exit(127);
        } else {
          int status;
          waitpid(child_pid, &status, 0);
          last_sts = WEXITSTATUS(status);
          do_print = 1;
        }
      }

      cmd = strtok_r(NULL, ";", &last_tok);
    }

    if (do_print && last_sts != 0) {
      printf("last command failed with status %d\n", last_sts);
    }

    if (strcmp(cmd_cp, "exit") == 0) {
      free(cmd);
      free(cmd_cp);
      return 0;
    }

    free(cmd);
    free(cmd_cp);
  }

  return 0;
}

