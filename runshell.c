#include "shell.h"
/**
 * run_shell -  run a simple shell processing command from a given input stream
 * @input_stream: a pointer to input stream to read commands from
 *
 * Return: no return value
 */
void run_shell(FILE *input_stream)
{
        char command[MAX_CMD_LENGTH];
        int interactive;
        size_t len;
        int status;
        int last_exit_status = 0;
        pid_t shell_pid = getpid();

        interactive = isatty(STDIN_FILENO);

        while (1)
        {
                if (interactive)
                {
                        printf("$ ");
                }

                if (input_stream == stdin)
                {
                        if (!get_user_input(command, MAX_CMD_LENGTH, input_stream))
                        {
                                break;
                        }
                }
                else
                {
                        if (fgets(command, MAX_CMD_LENGTH, input_stream) == NULL)
                        {
                                break;
                        }

                        len = strlen(command);

                        if (len > 0 && command[len - 1] == '\n')
                        {
                                command[len - 1] = '\0';
                        }
                }
                if (command[0] == '#')
                {
                        continue;
                }
                if (strncmp(command, "exit", 4) == 0)
                {
                        if (sscanf(command, "exit %d", &status) == 1)
                        {
                                exit(status);
                        }
                        else
                        {
                                /*printf("./shell: No such file or directory\n");*/
                                exit(status);
                        }
                }
                else if (strcmp(command, "env") == 0)
                {
                        print_environment_variables();
                }
                else if (strcmp(command, "quit") == 0)
                {
                        printf("Goodbye!\n");
                        break;
                }
                else if (strncmp(command, "setenv", 6) == 0)
                {
                        char variable[MAX_CMD_LENGTH];
                        char value[MAX_CMD_LENGTH];

                        if (sscanf(command, "setenv %s %s", variable, value) == 2)
                        {
                                set_environment_variable(variable, value);
                        }
                        else
                        {
                                fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                        }
                }
                else if (strncmp(command, "unsetenv", 8) == 0)
                {
                        char variable[MAX_CMD_LENGTH];

                        if (sscanf(command, "unsetenv %s", variable) == 1)
                        {
                                unset_environment_variable(variable);
                        }
                        else
                        {
                                fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                        }
                }
                else if (strncmp(command, "echo $?", 7) == 0)
                {
                        printf("%d\n", last_exit_status);
                }
                else if (strncmp(command, "echo $$", 7) == 0)
                {
                        printf("%d\n", shell_pid);
                }
                else if (strncmp(command, "echo $PATH", 10) == 0)
                {
                        char *path_value = getenv("PATH");

                        if (path_value != NULL)
                        {
                                printf("%s\n", path_value);
                        }
                        else
                        {
                                fprintf(stderr, "PATH is not set\n");
                        }
                }
                else if (strchr(command, '|') != NULL)
                {
                        char *cmd1 = strtok(command, "|");
                        char *cmd2 = strtok(NULL, "|");

                        trim_whitespace(cmd1);
                        trim_whitespace(cmd2);

                        if (strlen(cmd1) > 0 && strlen(cmd2) > 0)
                        {
                                exec_piped_commands(cmd1, cmd2);
                        }
                        else
                        {
                                printf("./shell: Invalid piped command\n");
                        }
                }
                else if (is_valid_command(command))
                {
                        fork_and_execute_command(command, &last_exit_status);
                }
                else
                {
                        printf("./shell: No such file or directory\n");
                }
        }

        if (!interactive && input_stream != stdin)
        {
                fclose(input_stream);
        }
}
