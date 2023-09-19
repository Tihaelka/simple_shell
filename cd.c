#include "shell.h"
/**
 * update_pwd_variable - update "PWD" variable to the current working directory
 *
 * Retrn: void
 */
void update_pwd_variable()
{
	char cwd[MAX_PATH_LENGTH];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", cwd, 1);
	}
	else
	{
		perror("getcwd");
	}
}
