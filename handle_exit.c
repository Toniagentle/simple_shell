#include "main.h"

/**
 * _handle_exit - Handle the exit buitin
 * @exit_arguments: The exit command passed
 * @no_of_args: Number of command passed
 * Return: Nothing
*/
void _handle_exit(char **exit_arguments, size_t no_of_args)
{
	int status = EXIT_SUCCESS;

	if (exit_arguments[1] != NULL)
	{
		status = _atoi(exit_arguments[1]);
	}

	_free_vector(exit_arguments, no_of_args);
	exit(status);
}
