#include "shell.h"
void exit_status(int exit_code, char *av[])
{
        if (av[1])
        {
                int code = strtol(av[1], NULL, 10);
                if (code >= 0 && code <= 255)
                {
                        printf("\n");
                        exit(code);
                }
                else
                {
                        fprintf(stderr, "./hsh: exit: %s: argument needed\n",
                                        av[1]);
                }
        }
        else
        {
                printf("$ \n");
                exit(exit_code);
        }
}

