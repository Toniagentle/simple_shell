#include "main.h"

/**
 * _handle_builtin_command - Handle the builtin commands
 * @command: The command to be executed.
 *
 * Return: Nothing (void).
 */
void _handle_builtin_command(char *command)
{
	int i;

	i = 0;
	if (_strcmp("env", command) == 0)
	{
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
	}
	else
		printf("Error: Unknown command '%s'\n", command);
}
