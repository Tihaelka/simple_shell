#include "main.h"
/**
 * exit_status - handles the exit status of the shell
 * @exit_code: the code to be used when exiting the shell
 * @av: an array of strings containing command line
 * arguments
 * Return: no return
 */
void exit_status(int exit_code, char *av[])
{
	int code;
	(void)exit_code;

	if (av[1])
	{
		code = strtol(av[1], NULL, 10);
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
			exit(0);
		}
}
